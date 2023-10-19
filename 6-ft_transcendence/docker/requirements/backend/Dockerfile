FROM	node:latest

LABEL version="1.0"

RUN mkdir /app
WORKDIR	/app

# get rid of data folder
# Copy
COPY data/src .
COPY data/package.json .
COPY data/tsconfig.json .
COPY data/package-lock.json .

RUN npm install

RUN npm run build

EXPOSE	3000

CMD ["npm", "run", "start:prod"]
