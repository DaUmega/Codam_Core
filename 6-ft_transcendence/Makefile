all:
	docker-compose -f docker/docker-compose.yml up -d --build

down:
	docker-compose -f docker/docker-compose.yml down

postgres:
	@docker run --name postgres_dev -d -p 5432:5432 --env-file=docker/.env postgres:latest

re:
	docker-compose -f docker/docker-compose.yml up -d --build

clean:
	docker stop $$(docker ps -qa);\
	docker rm $$(docker ps -qa);\
	docker rmi -f $$(docker images -qa);\
	docker volume rm $$(docker volume ls -q);\
	docker network rm $$(docker network ls -q);\

.PHONY: all re down clean
