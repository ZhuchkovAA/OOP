import requests
import time
import os
import sys

def load_file_git(path_to, file_name):
    url = f"https://raw.githubusercontent.com/ZhuchkovAA/OOP/main/renamer/{file_name}"
    response = requests.get(url)

    if response.status_code == 200:
        with open(file_name, 'w+', encoding='utf8') as file:
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
        'files': {
            'general': 0,
            'success': 0,
            'fail': 0
        },
        'dirs': {
            'general': 0,
            'success': 0,
            'fail': 0
        }
    }

    additional.animated_loading()

    for root, dirs, files in os.walk(directory):
        for filename in files:
            counter['files']['general'] += 1
            try:
                result = replace_name(name_project, filename, root)
                path_ = result['path']

                with open(path_['new'], 'r') as file:
                    content = file.read()
                content = content.replace(name_project['old'], name_project['new'])
                with open(path_['new'], 'w') as file:
                    file.write(content)

                counter['files']['success'] += 1
            except:
                counter['files']['fail'] += 1

        for foldername in dirs:
            counter['dirs']['general'] += 1
            try:
                result = replace_name(name_project, foldername, root)
                path_ =  result['path']
                rename_project(path_['new'], name_project)
                counter['dirs']['success'] += 1
            except:
                counter['dirs']['fail'] += 1

    return counter

def add_dependencies():
    try: 
        import dependencies
        if (dependencies.Dependencies().version != '1.0.4'): raise Exception('Not actual version')
    except:
        load_file_git({'root' : '/'}, 'dependencies.py')

    from dependencies import Dependencies 
    Dependencies = Dependencies()

    classes_dependencies = Dependencies.load_dependencies()

    return [ Dependencies, classes_dependencies]

def main():
    Dependencies, classes_dependencies = add_dependencies()

    try:
        Structures = classes_dependencies['structures']
    except:
        print('Не все зависимости подгрузились. Обратитесь к @ZhuchkovAA')
        time.sleep(100)
        return

    from git import update_project
    from additional import animated_loading

    update_project(Dependencies.path_to, Dependencies.files['all'])

    print(f'Version: {Dependencies.version}')
    print('\nПеред изменением имени файлов рекомендуется:\n    1. Закрыть Visual Studio\n    2. Удалить папки x64, bin, obj, .vs\n')

    Structures.replaсe_data['directory'] = input("Директория с проектом: ").replace("\\", "/")
    Structures.replaсe_data['name_project']['old'] = input("Старая Фамилия: ")
    Structures.replaсe_data['name_project']['new'] = input("Новая Фамилия: ")

    if (input(f"\n\nДиректория: {Structures.replaсe_data['directory']}\n{Structures.replaсe_data['name_project']['old']} меняю на {Structures.replaсe_data['name_project']['new']}\n                 [yes/no]: ") in ['y', 'yes']):
        counter = rename_project(Structures.replaсe_data['directory'], Structures.replaсe_data['name_project'])
        print(f"\nВсего Файлов: {counter['files']['general']}\nУспешно заменили: {counter['files']['success']}\nНе удалось открыть: {counter['files']['fail']}")
        print(f"\nВсего Папок: {counter['dirs']['general']}\nУспешно заменили: {counter['dirs']['success']}\nНе удалось открыть: {counter['dirs']['fail']}")

        print('\nP.S. Файлы которые не удалось открыть - скорее всего служебные/результат сборки, в них нет Фамилии автора.')
    else:
        print('Завершение программы...')

    print("\n\nGitHub: https://github.com/ZhuchkovAA")
    time.sleep(100)

if __name__ == '__main__':
    main()
