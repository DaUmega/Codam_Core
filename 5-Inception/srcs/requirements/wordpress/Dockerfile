FROM	debian:buster

RUN	apt update -y && \
        apt-get upgrade -y && \
        apt-get install -y php \
        php-mysql \
        php-cli \
        php-mbstring \
        php-fpm \
        php-gettext \
        mariadb-client \
        wget && \
        rm -rf /etc/php/7.3/fpm/pool.d/www.conf && \
        mkdir -p /run/php

COPY	conf/www.conf /etc/php/7.3/fpm/pool.d/

RUN 	mkdir -p /run/php

COPY	tools/init.sh /tmp/
RUN		chmod +x /tmp/init.sh
ENTRYPOINT	["/tmp/init.sh"]

WORKDIR	/var/www/html/

EXPOSE	9000

CMD		["php-fpm7.3", "-F"]