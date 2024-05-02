#FROM nodered/node-red:latest
FROM nodered/node-red


#RUN npm install -g npm@latest
RUN npm install --unsafe-perm --no-update-notifier --no-fund --only=production

#RUN npm install node-red-dashboard node-red-node-mysql
RUN npm install @flowfuse/node-red-dashboard node-red-node-mysql

WORKDIR /usr/src/node-red

COPY ./loading.html /usr/src/node-red/node_modules/node-red-dashboard/dist/

USER node-red

EXPOSE 1880

CMD ["npm", "start"]