FROM alpine

RUN apk update && \
	echo "y" | apk add --no-cache alpine-sdk bash libacl

WORKDIR /app

COPY . .

CMD ["sleep", "1000000000"]