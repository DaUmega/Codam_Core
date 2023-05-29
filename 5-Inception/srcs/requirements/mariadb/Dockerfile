FROM debian:buster

RUN		apt-get update -yq && \
        apt-get upgrade -y && \
        apt-get install mariadb-server \
        mariadb-client -y && \
        mkdir -p /var/run/mysqld && \
        chown -R kali:kali /var/run/mysqld && \
        chown -R kali:kali /etc/mysql/

COPY    ./tools/mariadb.sh /tmp/
COPY    ./conf/init.sql /tmp/
COPY    ./conf/my.cnf /etc/mysql

RUN     chmod 777 /tmp/mariadb.sh && chown -R kali:kali /tmp/ && \
        chown -R kali:kali /etc/mysql

EXPOSE 3306

ENTRYPOINT [ "/tmp/mariadb.sh" ]