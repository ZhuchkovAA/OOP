import os

def replace_name(name : dict, names : list, root, path):
    if name['old'] in names:
        path['old'] = os.path.join(root, names)
        new_names = names.replace(name['old'], name['new']) 
        path['new'] = os.path.join(root, new_names)
        os.rename(path['old'], path['new'])

    return { 'path' : path }

def rename_project(startpath, name_project):
    counter = {
        'general': 0,
        'success': 0,
        'fail': 0
    }
    for root, dirs, files in os.walk(startpath):
        for filename in files:
            counter['general'] += 1
            try:

                result = replace_name(name_project, filename, root, path)
                path =  result['path']

                with open(path['new'], 'r') as file:
                    content = file.read()
                content = content.replace(name_project['old'], name_project['new'])
                with open(path['new'], 'w') as file:
                    file.write(content)

                counter['success'] += 1
            except:
                counter['fail'] += 1

        for foldername in dirs:
            try:
                result = replace_name(name_project, foldername, root, path)
                path =  result['path']

                rename_project(path['new'], name_project)
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


    data['directory'] = input("Директория: ").replace("\\", "/")
    data['name_project']['old'] = input("Старая Фамилия: ")
    data['name_project']['new'] = input("Новая Фамилия: ")
    
    if (input(f"\n\nДиректория: {data['directory']}\n{data['name_project']['old']} меняю на {data['name_project']['new']}\n       [yes/no]: ") in ['y', 'yes']):
        results = rename_project(data['directory'], data['name_project'])
        print(f"\nВсего файлов: {results['general']}\nУспешно заменили: {results['success']}\nНе удалось открыть: {results['fail']}")

        print('\nP.S. Файлы которые не удалось открыть - скорее всего служебные, в них нет Фамилии автора.\nОтблагодарить можно пивом')
    else:
        print("Выход... ")

if __name__ == '__main__':
    main()
