
import requests
import subprocess
import time
import shutil
import os

def get_file_git():
    url = "https://raw.githubusercontent.com/ZhuchkovAA/OOP/main/renamer/main.py"
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        return None

def get_file_local(path_to):
    with open(path_to['root'] + 'main.py', "r", encoding='utf8') as file:
        return file.read()
    return None

def is_equal_files(path_to):
    git = get_file_git()
    local = get_file_local(path_to)

    if git == None: 
        print('Ошибка сети..')
        return { 'success' : True }

    if (hash(git) == hash(local)): return { 'success' : True }
    return { 'success' : False,  'files' : {'git' : git, 'local' : local}}

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

def update_project(path_to):
    print('Проверка обновлений...')
    response = is_equal_files(path_to) 
    if response['success']: return False

    print('Установка обновлений...')

    with open(path_to['root'] + 'main.py', 'w', encoding='utf8') as file:
        file.write(response['files']['git'])
        create_exe(path_to)

    print('Требуется перезагрузка...')
    time.sleep(1000)
    return True
