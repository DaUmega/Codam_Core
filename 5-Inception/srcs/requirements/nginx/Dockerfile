FROM	debian:buster

RUN		apt-get update && apt-get install -y nginx openssl \
		&& mkdir /etc/nginx/ssl && mkdir -p /run/nginx \
		&& chown -R kali /var/lib/nginx \
		&& rm -rf /etc/nginx/sites-available/default

COPY	conf/default.conf /etc/nginx/sites-available/default.conf
COPY    conf/nginx.conf /etc/nginx/nginx.conf

RUN		mkdir -p /var/www/html/wordpress && chown -R kali /var/www/html/wordpress
RUN		ln -s /etc/nginx/sites-available/default.conf /etc/nginx/sites-enabled/default.conf
RUN		openssl req -newkey rsa:4096 -x509 -sha256 -days 365 \
		-nodes -out /etc/nginx/ssl/pdong.crt \
		-keyout /etc/nginx/ssl/pdong.key \
		-subj "/C=NL/ST=Amsterdam/L=Amsterdam/O=Codam/OU=pdong/CN=pdong.42.fr"

RUN		sed -i 's|DOMAIN_NAME|pdong.42.fr|g' /etc/nginx/sites-available/default.conf \
		&& sed -i 's|WP_PATH|\/var\/www\/html\/wordpress|g' /etc/nginx/sites-available/default.conf \
		&& sed -i 's|PHP_HOST|wordpress|g' /etc/nginx/sites-available/default.conf \
		&& sed -i 's|PHP_PORT|9000|g' /etc/nginx/sites-available/default.conf \
		&& sed -i 's|CERTS_KEY|\/etc\/nginx\/ssl\/pdong.key|g' /etc/nginx/sites-available/default.conf \
		&& sed -i 's|CERTS_CRT|\/etc\/nginx\/ssl\/pdong.crt|g' /etc/nginx/sites-available/default.conf

EXPOSE	443

CMD		["nginx", "-g", "daemon off;"]