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
fi
