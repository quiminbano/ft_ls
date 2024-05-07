FROM alpine

RUN apk update && \
	echo "y" | apk add --no-cache alpine-sdk bash

WORKDIR /app

COPY . .

CMD ["sleep", "1000000000"]