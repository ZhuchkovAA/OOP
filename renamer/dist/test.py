
print('Установка обновлений...')

for files in [{'name' : 'testtt.py', 'git' : 'testtt'}]:
    print(files['name'])
    with open(files['name'], 'w+', encoding='utf8') as file:
        file.write(files['git'])

