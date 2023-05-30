#!/bin/sh

sed -i 's|PHP_PORT|9000|g' /etc/php/7.3/fpm/pool.d/www.conf

if [ -f /var/www/html/wordpress/wp-config.php ]
then
	echo "wordpress already installed"
else
	wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp
	wp core download --path=/var/www/html/wordpress --allow-root
	wp config create --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=mariadb --path=/var/www/html --skip-check --allow-root
	wp core install --path=/var/www/html/wordpress --url=$DOMAIN_NAME --title=Inception --admin_user=$WP_DB_ADMIN --admin_password=$WP_DB_ADMIN_PASSWORD --admin_email=$WP_DB_EMAIL --skip-email --allow-root
	wp theme install teluro --path=/var/www/html/wordpress --activate --allow-root
	wp user create $WP_DB_USER $WP_DB_USER_EMAIL --role=author --path=/var/www/html/wordpress --user_pass=$WP_DB_PASSWORD --allow-root
fi

/usr/sbin/php-fpm7.3 -F