using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace CS_DASM
{
    class AssemblyInfo
    {
        public static Assembly asm;
        public static List<Module> modules = new List<Module>();
        public static List<MethodInfo> m_methods = new List<MethodInfo>();
        
        public AssemblyInfo() { asm = null;  }
        public AssemblyInfo(string path) { asm = Assembly.LoadFile(path); }
        public AssemblyInfo(string path, ref TreeView tree)
        {
            ImageList imglist = new ImageList();
            
            asm = Assembly.LoadFile(path);
            AssemblyInfo.MakeTreeView(ref tree);
        }
        public Module[] GetModules() { return asm.GetModules(); }
        public static void MakeTreeView(ref TreeView tree)
        {
            // 0.최상위 노드, 파일 이름
            TreeNode file = new TreeNode(asm.CodeBase, 0, 0);
            tree.Nodes.Add(file);
            
            // 1. MANIFEST
            Module manifestmodule = asm.ManifestModule;
            modules.Add(manifestmodule);
            TreeNode manifest = new TreeNode("MANIFEST",1,1);
            file.Nodes.Add("m.1","manifest",1,1);

            
            // 1. 모듈(namespace)
            Module[] namespaces = asm.GetModules();

            int methodindex = 0;
            foreach (Module module in namespaces)
	        {
                modules.Add(module);
	            TreeNode namespacenode = new TreeNode(module.Name,2,2);
	            
                // 2. class
                Type[] classes = asm.GetTypes();
                
                foreach (Type cls in classes)
                {
                    TreeNode classnode = new TreeNode(module.Name+"."+ cls.Name, 3, 3);
                    
                    // 3. method
                    MethodInfo[] methods = cls.GetMethods(BindingFlags.DeclaredOnly | BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Static | BindingFlags.Instance);
                    
                    foreach(MethodInfo method in methods)
                    {
                        TreeNode methodenode = new TreeNode(method.Name, 4, 4);
                        
                        if(method.GetMethodBody() != null)
                        {
                            methodenode.Tag = methodindex++;
                            AssemblyInfo.m_methods.Add(method);
                        }
                            

                        classnode.Nodes.Add(methodenode);
                        
                    }

                    // 4. feild
                    FieldInfo[] fields = cls.GetFields(BindingFlags.NonPublic|BindingFlags.Public|BindingFlags.Static|BindingFlags.Instance);
                    foreach (FieldInfo field in fields)
                    {
                        TreeNode fieldnode = new TreeNode(field.Name, 5, 5);
                        
                        fieldnode = new TreeNode(field.Name, 5, 5);
                        
                        classnode.Nodes.Add(fieldnode);
                    }

                    //5. constructor
                    ConstructorInfo[] constructors = cls.GetConstructors(BindingFlags.DeclaredOnly | BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Static | BindingFlags.Instance);
                    foreach (ConstructorInfo constructor in constructors)
                    {
                        TreeNode constructornode = new TreeNode(constructor.Name + constructor.GetMethodBody().GetILAsByteArray().ToString(), 6, 6);
                        //constructornode.Tag = methodindex++;
                        //AssemblyInfo.m_methods.Add(constructor);
                        classnode.Nodes.Add(constructornode);
                    }

                    //6. property
                    PropertyInfo[] properties = cls.GetProperties();
                    foreach (PropertyInfo property in properties)
	                {
                        TreeNode propertynode = new TreeNode(property.Name, 7,7);
                        classnode.Nodes.Add(propertynode);
	                }
                    namespacenode.Nodes.Add(classnode);
                }
                
                file.Nodes.Add(namespacenode);
	        }

            //Module[] modules = asm.GetModules();
            //foreach(Module module in modules)
            //{
            //    tree.Nodes[0].Nodes.Add(module.Name);
            //}
        }
        public static void PrintModules(Module[] modules)
        {
            foreach (Module module in modules)
            {
                Console.WriteLine(module.Name);
            }
        }
        public static void PrintMethods(MethodInfo[] methods)
        {
            foreach (MethodInfo method in methods)
            {
                Console.WriteLine(method.Name);
            }
        }
        public static void PrintParameters(ParameterInfo[] parameters)
        {

            String str = "(";
            foreach (ParameterInfo parameter in parameters)
            {
                str += parameter.Name;
                str += ",";
            }
            str += ")";
            Console.WriteLine(str);
        }
        public static void PrintFeilds(FieldInfo[] fields)
        {
            foreach (FieldInfo field in fields)
            {
                Console.WriteLine(field.Name);
            }
        }
    }
}
