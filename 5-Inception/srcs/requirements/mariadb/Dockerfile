FROM debian:buster

RUN	apt-get update -yq && \
        apt-get upgrade -y && \
        apt-get install mariadb-server \
        mariadb-client -y && \
        mkdir -p /var/run/mysqld && \
        chown -R mysql:mysql /var/run/mysqld && \
        chown -R mysql:mysql /etc/mysql/

COPY    ./tools/mariadb.sh /tmp/
COPY    ./conf/init.sql /tmp/
COPY    ./conf/my.cnf /etc/mysql

RUN     chmod 777 /tmp/mariadb.sh && chown -R mysql:mysql /tmp/ && \
        chown -R mysql:mysql /etc/mysql

USER    mysql

EXPOSE 3306

ENTRYPOINT [ "/tmp/mariadb.sh" ]