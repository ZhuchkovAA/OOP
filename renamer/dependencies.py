class Dependencies:
    def __init__(self):
        self.version = '1.0.0'
        
        self.is_exe = True
        self.files = { 
            'all': ['main.py', 'git.py', 'additional.py', 'dependencies.py', 'structures.py'],
            'dependencies': ['git', 'additional', 'structuresss'],
            'classes': ['structures']
        }

        self.path_to = {}
        if (self.is_exe): self.path_to['root'] = '../'
        else: self.path_to['root'] = ''

    def load_dependencies(self, is_downloaded, is_test=False):
        import time
        import sys
        import os
        
        result = {}

        parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
        sys.path.append(parent_dir)

        print(sys.path)
        time.sleep(3)

        from main import load_file_git

        for module_name in self.files['dependencies']:
            try:
                import_module = __import__(module_name)
                print(module_name)
            except:
                if (is_test): continue
                load_file_git(self.path_to, module_name + '.py')
                is_downloaded = True

        for module_class_name in self.files['classes']:
            try:
                import_module = __import__(module_class_name)
                print(module_class_name)
                time.sleep(2)
                module_class = getattr(import_module, module_class_name.capitalize())
                result[module_class_name] = module_class()
            except:
                if (is_test): continue
                load_file_git(self.path_to, module_class_name + '.py')
                is_downloaded = True

        return result
