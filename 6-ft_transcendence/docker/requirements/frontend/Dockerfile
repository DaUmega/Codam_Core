FROM	node:latest

RUN     mkdir -p /var/www/html/frontend

WORKDIR	/var/www/html/frontend

COPY    ./data/package.json .

RUN     yarn install

EXPOSE	80

CMD     yarn run serve --port 80