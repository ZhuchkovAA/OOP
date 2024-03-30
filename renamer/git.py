import requests
import subprocess
import time
import shutil
import os
import time
import sys
import subprocess

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
    
    if (len(not_equal_files)):
        return { 'success' : True }

    return { 'success' : False,  'files' : not_equal_files}

def create_exe(path_to):
    subprocess.run(["pyinstaller", "--onefile", path_to['root'] + 'main.py'], check=True)

    try: 
        shutil.rmtree("dist")
        shutil.rmtree("build")
        os.remove('main.spec')
        shutil.rmtree(path_to['root'] + "build")
        os.remove(path_to['root'] + 'main.spec')
        shutil.rmtree(path_to['root'] + "__pycache__")
    except:
        pass

def update_project(path_to, files):

    print('Проверка обновлений...')

    response = is_equal_files(path_to, files) 
    if response['success']: return False

    print('Установка обновлений...')

    for files in response['files']:
        print(files['name'])
        with open(files['name'], 'w+', encoding='utf8') as file:
            file.write(files['git'])

    # create_exe(path_to)

    # print('Требуется перезагрузка...')
    # time.sleep(1000)
    return False
