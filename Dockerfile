FROM gcc:latest AS build
RUN apt-get update && apt-get install -y cmake
WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && cmake --build .

FROM ubuntu:latest
COPY --from=build /app/build/blackjack-server /usr/local/bin/
EXPOSE 8081
CMD ["blackjack-server"]