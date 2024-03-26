
import requests
import subprocess

def get_file_git():
    url = "https://raw.githubusercontent.com/ZhuchkovAA/OOP/main/renamer/main.py"
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        return None

def get_file_local():
    with open('main.py', "r", encoding='utf8') as file:
        return file.read()

def is_equal_files():
    git = get_file_git()
    local = get_file_local()

    if git == None: 
        print('Ошибка сети..')
        return { 'success' : True }

    if (hash(git) == hash(local)): return { 'success' : True }
    return { 'success' : False,  'files' : {'git' : git, 'local' : local}}

def update_project():
    print('Проверка обновлений...')
    response = is_equal_files() 
    if response['success']: return False

    print('Установка обновлений...')
    with open('main.py', 'w', encoding='utf8') as file:
        file.write(response['files']['git'])
        subprocess.run(["pyinstaller", "--onefile", "main.py"], check=True)

    print('Требуестся перезагрузка...')
    return True




     
