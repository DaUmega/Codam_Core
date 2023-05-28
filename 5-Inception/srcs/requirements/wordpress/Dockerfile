FROM	debian:buster

RUN		apt-get update && apt-get install -y wget curl bash \
		php php-cgi php-mysql php-fpm php-gd php-cli
RUN		curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
		&& chmod +x wp-cli.phar \
		&& mv wp-cli.phar /usr/local/bin/wp

COPY	./conf/www.conf /etc/php/7.3/fpm/pool.d/

RUN 	mkdir -p /run/php

COPY	./tools/init.sh /usr/local/bin/
RUN		chmod +x /usr/local/bin/init.sh
ENTRYPOINT	["/usr/local/bin/init.sh"]

WORKDIR	/var/www/html/

EXPOSE	9000

CMD		[ "/usr/sbin/php-fpm7.3", "-F" ]