import sys
sys.path.append('../')  # Добавляем путь к каталогу, содержащему модуль

test = False

from dependencies import Dependencies
Dependencies = Dependencies()

classes_dependencies = Dependencies.has_dependencies(is_downloaded)
