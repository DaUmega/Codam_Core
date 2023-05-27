FROM	debian:buster

RUN		apt -y update && apt install -y nginx openssl \
		&& mkdir /etc/nginx/ssl 
RUN		openssl req -newkey rsa:4096 -x509 -sha256 -days 365 \
		-nodes -out /etc/nginx/ssl/pdong.crt \
		-keyout /etc/nginx/ssl/pdong.key \
		-subj "/C=NL/ST=Amsterdam/L=Amsterdam/O=Codam/OU=pdong/CN=${DOMAIN_NAME}/"

COPY	./conf/nginx.conf /etc/nginx/conf.d

RUN 	mkdir -p /run/nginx

EXPOSE	443

CMD		[ "nginx", "-g", "daemon off;" ]