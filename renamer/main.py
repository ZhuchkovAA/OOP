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
    url = f"https://raw.githubusercontent.com/ZhuchkovAA/OOP/main/renamer/{file_name}"
    response = requests.get(url)

    if response.status_code == 200:
        with open(path_to['root'] + file_name, 'w', encoding='utf8') as file:
            file.write(response.text)

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

def check_files():
    is_downloaded = False

    try: 
        from dependencies import Dependencies
    except: 
        load_file_git({'root' : '../'}, 'dependencies.py')
        from dependencies import Dependencies
        is_downloaded = True

    Dependencies = Dependencies()

    try: 
        from git import create_exe
        from git import has_git
    except: 
        load_file_git(Dependencies.path_to, 'git.py')
        is_downloaded = True

    try: 
        from additional import has_additional
    except: 
        load_file_git(Dependencies.path_to, 'additional.py')
        is_downloaded = True

    if (is_downloaded): create_exe(Dependencies.path_to)

    return Dependencies

def main():

    Dependencies = check_files()
    
    if (update_project(Dependencies.path_to, Dependencies.files)): return
    
    print('\nПеред изменением имени файлов рекомендуется:\n    1. Закрыть Visual Studio\n    2. Удалить папки x64, bin, obj, .vs\n')

    Dependencies.data['directory'] = input("Директория с проектом: ").replace("\\", "/")
    Dependencies.data['name_project']['old'] = input("Старая Фамилия: ")
    Dependencies.data['name_project']['new'] = input("Новая Фамилия: ")

    if (input(f"\n\nДиректория: {Dependencies.data['directory']}\n{Dependencies.data['name_project']['old']} меняю на {Dependencies.data['name_project']['new']}\n                 [yes/no]: ") in ['y', 'yes']):
        counter = rename_project(data['directory'], data['name_project'])
        print(f"\nВсего: {counter['general']}\nУспешно заменили: {counter['success']}\nНе удалось открыть: {counter['fail']}")

        print('\nP.S. Файлы которые не удалось открыть - скорее всего служебные/результат сборки, в них нет Фамилии автора.')
    else:
        print('Завершение программы...')

    print("\n\nGitHub: https://github.com/ZhuchkovAA")
    time.sleep(3)

if __name__ == '__main__':
    main()
