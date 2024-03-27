import requests
import subprocess
import time
import shutil
import os
import time
import sys
import subprocess

from git import update_project
from additional import animated_loading

def load_file_git(path_to, file_name):
    print(f'Скачавается файл {file_name}    ')

    animated_loading()

    url = f"https://raw.githubusercontent.com/ZhuchkovAA/OOP/main/renamer/{file_name}"
    response = requests.get(url)
    if response.status_code == 200:
        with open(path_to['root'] + file_name, 'w', encoding='utf8') as file:
            file.write(response.text)
    else:
        print(f'Not found file "{file_name}" on git')

    sys.stdout.write('\r' + ' ' * 20 + '\r')
    sys.stdout.flush()

# Для особо одарённых, я засунул всё в один файл тупо из-за того что exe нормально не компилился, а ебаться с этим желания ноль..

def replace_name(name, names, root):
    path_ = {
        'old' : None,
        'new' : None,
    }

    names = {
        'old' : names,
        'new' : None
    }

    if name['old'] in names['old']:
        path_['old'] = os.path.join(root, names['old'])
        names['new'] = names['old'].replace(name['old'], name['new']) 
        path_['new'] = os.path.join(root, names['new'])
        os.rename(path_['old'], path_['new'])

    if (path_['old'] == None): 
        path_['new'] = os.path.join(root, names['old'])

    return { 'path' : path_ }

def rename_project(directory, name_project):
    counter = {
        'general': 0,
        'success': 0,
        'fail': 0
    }

    animated_loading()

    for root, dirs, files in os.walk(directory):
        for filename in files:
            counter['general'] += 1
            try:
                result = replace_name(name_project, filename, root)
                path_ = result['path']

                with open(path_['new'], 'r') as file:
                    content = file.read()
                content = content.replace(name_project['old'], name_project['new'])
                with open(path_['new'], 'w') as file:
                    file.write(content)

                counter['success'] += 1
            except:
                counter['fail'] += 1

        for foldername in dirs:
            try:
                result = replace_name(name_project, foldername, root)
                path_ =  result['path']

                rename_project(path_['new'], name_project)
            except:
                pass

    return counter


def main():
    data = {
        'name_project' : {
            'old' : None,
            'new' : None
        },
        'directory' : None 
    }

    is_exe = True
    files = ['main.py', 'git.py', 'additional.py']

    path_to = {}
    if (is_exe): path_to['root'] = '../'
    else: path_to['root'] = ''

    is_downloaded = False

    try: 
        from git import create_exe
        from git import has_git
    except: 
        load_file_git(path_to, 'git.py')
        is_downloaded = True

    try: from git import has_additional
    except: 
        load_file_git(path_to, 'additional.py')
        is_downloaded = True

    if (is_downloaded): create_exe(path_to)

    if (update_project(path_to, files)): return
    
    print('\nПеред изменением имени файлов рекомендуется:\n    1. Закрыть Visual Studio\n    2. Удалить папки x64, bin, obj, .vs\n')

    data['directory'] = input("Директория с проектом: ").replace("\\", "/")
    data['name_project']['old'] = input("Старая Фамилия: ")
    data['name_project']['new'] = input("Новая Фамилия: ")

    # data['directory'] = 'C:/Users/lesha/Documents/GitHub/OOP/ZhuchkovLab1'
    # data['name_project']['old'] = 'Zhuchkov'
    # data['name_project']['new'] = 'Test'

    # data['name_project']['old'] = 'Test'
    # data['name_project']['new'] = 'Zhuchkov'

    
    if (input(f"\n\nДиректория: {data['directory']}\n{data['name_project']['old']} меняю на {data['name_project']['new']}\n                 [yes/no]: ") in ['y', 'yes']):
        counter = rename_project(data['directory'], data['name_project'])
        print(f"\nВсего: {counter['general']}\nУспешно заменили: {counter['success']}\nНе удалось открыть: {counter['fail']}")

        print('\nP.S. Файлы которые не удалось открыть - скорее всего служебные/результат сборки, в них нет Фамилии автора.')
    else:
        print('Завершение программы...')

    print("\n\nGitHub: https://github.com/ZhuchkovAA")
    time.sleep(3)

if __name__ == '__main__':
    main()
