class Dependencies:
    def __init__(self):
        self.version = '1.0.42'
        
        self.is_exe = True
        self.files = { 
            'all': ['main.py', 'git.py', 'additional.py', 'dependencies.py', 'structures.py'],
            'dependencies': ['git', 'additional'],
            'classes': ['structures']
        }

        self.path_to = {}
        if (self.is_exe): self.path_to['root'] = '../'
        else: self.path_to['root'] = ''

    def load_libs(self):
        import os
        os.system('pip install requests==2.31.0')

    def load_dependencies(self, is_test=False):
        result = {}

        print('Загрузка библиотек...')
        self.load_libs()

        from main import load_file_git

        for module_name in self.files['dependencies']:
            try:
                import_module = __import__(module_name)
            except:
                if (is_test): continue
                load_file_git(self.path_to, module_name + '.py')

        for module_class_name in self.files['classes']:
            try:
                import_module = __import__(module_class_name)
                module_class = getattr(import_module, module_class_name.capitalize())
                result[module_class_name] = module_class()
            except:
                if (is_test): continue
                load_file_git(self.path_to, module_class_name + '.py')

            import_module = __import__(module_class_name)
            module_class = getattr(import_module, module_class_name.capitalize())
            result[module_class_name] = module_class()

        return result