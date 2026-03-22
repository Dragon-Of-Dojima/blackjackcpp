FROM gcc:latest AS build
WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && cmake --build .

FROM ubuntu:latest
COPY --from=build /app/build/blackjack-server /usr/local/bin/
EXPOSE 8081
CMD ["blackjack-server"]