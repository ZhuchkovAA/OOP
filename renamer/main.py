import os

def rename_all(startpath, old_name, new_name):
    counter = {
        'general': 0,
        'success': 0,
        'fail': 0
    }
    for root, dirs, files in os.walk(startpath):
        for filename in files:
            counter['general'] += 1
            try:
                old_path = os.path.join(root, filename)
                new_path = old_path

                if old_name in filename:  
                    new_filename = filename.replace(old_name, new_name) 
                    new_path = os.path.join(root, new_filename)
                    os.rename(old_path, new_path)

                with open(new_path, 'r') as file:
                    content = file.read()
                content = content.replace(old_name, new_name)
                with open(new_path, 'w') as file:
                    file.write(content)

                counter['success'] += 1
            except:
                counter['fail'] += 1

        for foldername in dirs:
            try:
                if old_name in foldername:
                    old_path = os.path.join(root, foldername)
                    new_foldername = foldername.replace(old_name, new_name)
                    new_path = os.path.join(root, new_foldername)
                    os.rename(old_path, new_path)
                    print(f'Renamed: \n{old_path}\nto\n{new_path} \n')
                    rename_all(new_path, old_name, new_name)
            except:
                pass
    return counter


def main():   
    directory = input("Директория: ").replace("\\", "/")
    old_name = input("Старая Фамилия: ")
    new_name = input("Новая Фамилия: ")
    
    if (input(f"\n\nДиректория: {directory}\n{old_name} меняю на {new_name}\n       [yes/no]: ") in ['y', 'yes']):
        data = rename_all(directory, old_name, new_name)
        print(f"\nВсего файлов: {data['general']}\nУспешно заменили: {data['success']}\nНе удалось открыть: {data['fail']}")

        print('\nP.S. Файлы которые не удалось открыть - скорее всего служебные, в них нет Фамилии автора.\nОтблагодарить можно пивом')
    else:
        print("Выход... ")

if __name__ == '__main__':
    main()
