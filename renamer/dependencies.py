class Dependencies:
    def __init__(self):
        self.version = '1.0.3'
        
        self.is_exe = True
        self.files = { 
            'all': ['main.py', 'Git.py', 'Additional.py', 'Dependencies.py', 'Structures.py'],
            'dependencies': ['Git', 'Additional'],
            'classes': ['Structures']
        }

        self.path_to = {}
        if (self.is_exe): self.path_to['root'] = '../'
        else: self.path_to['root'] = ''

    def load_dependencies(self):
        result = {}

        from main import load_file_git

        for module_name in self.files['dependencies']:
            try:
                import_module = __import__(module_name)
            except:
                load_file_git(self.path_to, module_name + '.py')

        for module_class_name in self.files['classes']:
            try:
                import_module = __import__(module_class_name)
                module_class = getattr(import_module, module_class_name.capitalize())
                result[module_class_name] = module_class()
                break
            except:
                load_file_git(self.path_to, module_class_name + '.py')

            import_module = __import__(module_class_name)
            module_class = getattr(import_module, module_class_name.capitalize())
            result[module_class_name] = module_class()

        return result
