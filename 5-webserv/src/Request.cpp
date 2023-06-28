#include <Request.hpp>

RequestHandler::RequestHandler(serverBlock &input, std::string &raw_string) : _copyBlock(input)
{
  this->_rawRequest = raw_string;
}

RequestHandler::~RequestHandler() {}

static std::vector<std::string> split(std::string s, std::string delim) {
  std::string token;
  std::size_t pos_start = 0;
  std::size_t pos_end;
  std::size_t delim_len = delim.length();
  std::vector<std::string> res;

  while ((pos_end = s.find(delim, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return (res);
}

// Public Methods
std::string RequestHandler::requestlineChecker() {
  this->parse();

  if (not this->methodChecker() || not this->uriChecker() || not this->versionChecker()
    || not this->endChecker())
    returnCode = "400";
  else if (not this->bodySizeChecker())
    returnCode = "413";
  else
    returnCode = "100";
  return (returnCode);
}


// Private Methods
void  RequestHandler::parse() {
  if (_rawRequest.find("Host:") == std::string::npos)
    return;

  std::size_t bodyStart = _rawRequest.find("\r\n\r\n");
  if (bodyStart != std::string::npos)
    body = _rawRequest.substr(bodyStart + 4);

  this->_requestLines = split(this->_rawRequest, "\r\n");
  std::vector<std::string>::iterator line = this->_requestLines.begin();

  std::vector<std::string> first_line = split(*line, " ");
  this->method = first_line[0];
  this->uri = first_line[1];
  if (uri[0] != '/')
    uri = uri.substr(uri.find('/', 7));
  this->version = first_line[2];

  // Skip the first line, we already stored them.
  line++;
  for (; not line->empty(); line++) {
    std::size_t first = line->find(":");
    std::string key = line->substr(0, first);
    std::string value = line->substr(first + 2, line->find_first_of(";") - key.length() - 2);
    if (key == "Content-Type" && contentTypeChecker(value)) {
      contentType = value;
    }
    this->reqValues.insert(std::pair<std::string, std::string>(key, value));
  }
}

bool  RequestHandler::methodChecker() {
    if (this->method != "GET" && this->method != "POST" && this->method != "DELETE")
      return (false);
    return (true);
}

bool  RequestHandler::uriChecker() {
  if (this->uri.empty() || this->uri[0] != '/')
    return (false);

  std::string invalidChars = "<>\"{}|\\^`#%[]";
  for (std::size_t i = 0; i < invalidChars.length(); i++)
    if (this->uri.find(invalidChars[i]) != std::string::npos)
      return (false);
  return (true);
}

bool  RequestHandler::versionChecker() {
  if (this->version.empty() || (this->version != "HTTP/1.1"
    && this->version != "HTTP/1.0" && this->version != "HTTP/2.0"))
    return (false);
  return (true);
}

bool  RequestHandler::contentTypeChecker(std::string value) {
  std::string validContentTypes[] = { "application/json", "application/javascript", "application/xml",
    "application/java-archive", "application/EDI-X12", "application/EDIFACT", "application/octet-stream",
    "application/ogg", "application/pdf", "application/xhtml+xml", "application/x-shockwave-flash", "application/ld+json",
    "application/zip", "application/x-www-form-urlencoded", "audio/mpeg", "audio/x-ms-wma", "audio/vnd.rn-realaudio",
    "audio/x-wav", "image/gif", "image/jpeg", "image/png", "image/tiff", "image/vnd.microsoft.icon", "image/x-icon",
    "image/vnd.djvu", "image/svg+xml", "multipart/mixed", "multipart/alternative", "multipart/related", "multipart/form-data",
    "text/css", "text/csv", "text/html", "text/javascript", "text/plain", "plain/text", "text/xml", "video/mpeg", "video/mp4",
    "video/quicktime", "video/x-ms-wmv", "video/x-msvideo", "video/x-flv", "video/webm" };
  std::string lowercaseValue = toLowerCase(value);
  for (std::size_t i = 0; i < (sizeof(validContentTypes) / sizeof(validContentTypes[0])); i++) {
    if (lowercaseValue == validContentTypes[i])
      return true;
  }
  _copyBlock._responseCode = "400";
  return false;
}

bool  RequestHandler::endChecker() {
  if ((method == "GET" || method == "DELETE") 
    && this->_rawRequest.compare(this->_rawRequest.length() - 4, 4, "\r\n\r\n") != 0)
    return (false);
  return (true);
}

bool  RequestHandler::bodySizeChecker() {
  if (std::strtoul(reqValues["Content-Length"].c_str(), NULL, 10) > _copyBlock._maxBodySize)
    return (false);
  return (true);
}

std::string RequestHandler::toLowerCase(const std::string &input)
{
  std::string ret = input;
  for (std::size_t i = 0; i < ret.length(); i++)
    ret[i] = std::tolower(ret[i]);
  return ret;
}
