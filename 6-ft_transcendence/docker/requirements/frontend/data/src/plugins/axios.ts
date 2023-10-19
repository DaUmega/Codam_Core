import axios from 'axios'

// Plugin allows to configure axios as HTTP client: make requests easy to backend by providing the base URL
// In API call in view: provide rest of the URL

// NEEDS_WORK
// CHANGE BASEURL TO URL OF WEBSITE AND SET AUTHORIZATION TO AUTH OF BACKEND
const siteIP = process.env.VUE_APP_SITE_IP
const apiKey = process.env.VUE_APP_SECRET

export const API = axios.create({
  baseURL: `http://${siteIP}:3000/${apiKey}/`,
  headers: {
    'Content-Type': 'application/json'
    // "Authorization": "Bearer " + process.env.VUE_APP_AUTH_TOKEN
  }
})
