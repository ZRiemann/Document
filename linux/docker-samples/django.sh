#!/bin/bash

dir=django
# remove the old django directory
if [ -d $dir ]; then
    echo "remove the old $dir directory"
    sudo rm -fr $dir
fi

mkdir ${dir}
cd ${dir}

echo "Create Docker file"
echo "FROM python:3
ENV PYTHONUNBUFFERED 1
RUN mkdir /code
WORKDIR /code
COPY requirements.txt /code/
RUN pip install -r requirements.txt
COPY . /code/" > Dockerfile

echo "Create requirements.txt"
echo "Django>=2.0,<3.0
psycopg2>=2.7,<3.0" > requirements.txt

echo "Create docker-compose.yml"
echo "version: '3'

services:
  db:
    image: postgres
  web:
    build: .
    command: python manage.py runserver 0.0.0.0:8000
    volumes:
      - .:/code
    ports:
      - "8000:8000"
    depends_on:
      - db
" > docker-compose.yml

echo "Create a Danjo project"
sudo docker-compose run web django-admin startproject composeexample .

echo "Change the ownership of the new file"
sudo chown -R $USER:$USER .

echo "Connect the database"
echo "add the follow code to <composeexample/settings.py>:
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': 'postgres',
        'USER': 'postgres',
        'HOST': 'db',
        'PORT': 5432,
    }
}
"
echo "press any key to continue. AFTER ADD CODE..."
read pick

echo "Run the docker-compose up"
echo "you can try <http://localhost:8000> on browser"
sudo docker-compose up

echo "Clean the django dir"
cd ..
sudo rm -fr $dir