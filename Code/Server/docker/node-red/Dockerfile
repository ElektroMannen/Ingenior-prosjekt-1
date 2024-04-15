FROM nodered/node-red:latest

RUN npm install -g npm@latest

RUN npm install node-red-dashboard node-red-node-mysql

WORKDIR /usr/src/node-red

USER node-red

EXPOSE 1880

CMD ["npm", "start"]