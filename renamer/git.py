import requests
import time
import os
import sys

def get_file_git(file_name):
    url = f"https://raw.githubusercontent.com/ZhuchkovAA/OOP/main/renamer/{file_name}"
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        return None

def get_file_local(path_to, file_name):
    with open(file_name, "r", encoding='utf8') as file:
        return file.read()
    return None

def is_equal_files(path_to, files):
    not_equal_files = []
    for file in files:

        git_file = get_file_git(file)
        local = get_file_local(path_to, file)

        if git_file == None: 
            print('Ошибка сети..')
            return { 'success' : True }

        if (hash(git_file) != hash(local)):
            not_equal_files.append({'name': file, 'git' : git_file, 'local' : local}) 
            print(f'Загрузка {file}')

    if (not len(not_equal_files)):
        return { 'success' : True }

    return { 'success' : False,  'files' : not_equal_files}

def update_project(path_to, files):

    print('Проверка обновлений...')

    response = is_equal_files(path_to, files) 
    if response['success']: return False

    for files in response['files']:
        with open(files['name'], 'w', encoding='utf8') as file:
            file.write(files['git'])
    return False
