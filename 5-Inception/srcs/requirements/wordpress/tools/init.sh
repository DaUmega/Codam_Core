#!/bin/sh

if [ -f ./wp-config.php ]
then
	echo "wordpress already installed"
else
	wget http://wordpress.org/latest.tar.gz
	tar xfz latest.tar.gz
	mv wordpress/* .
	rm -f latest.tar.gz
	rm -rf wordpress

	#Import env variables
	sed -i "s/pdong/$MYSQL_USER/g" wp-config-sample.php
	sed -i "s/test1234/$MYSQL_PASSWORD/g" wp-config-sample.php
	sed -i "s/localhost/$MYSQL_HOSTNAME/g" wp-config-sample.php
	sed -i "s/wordpress/$MYSQL_DATABASE/g" wp-config-sample.php
	cp wp-config-sample.php wp-config.php

	until mysqladmin -hmariadb -u${MYSQL_USER} -p${MYSQL_PASSWORD} ping; do
           sleep 2
    done
    wp core install --url="${DOMAIN_NAME}" --title="inception" --admin_user="${WP_DB_ADMIN}" --admin_password="${WP_DB_ADMIN_PASSWORD}" --admin_email="${WP_DB_EMAIL}" --allow-root
	wp user create ${WP_DB_USER} ${WP_DB_USER_EMAIL} --user_pass=${WP_DB_PASSWORD} --allow-root
fi

exec "$@"
exec /usr/sbin/php-fpm7.3 -F