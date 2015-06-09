using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Reflection.Emit;
using ILLib;

namespace cs_assem
{
    public static class Globals
    {
        public static Dictionary<int, object> Cache = new Dictionary<int, object>();

        public static OpCode[] multiByteOpCodes;
        public static OpCode[] singleByteOpCodes;
        public static Module[] modules = null;

        public static void LoadOpCodes()
        {
            singleByteOpCodes = new OpCode[0x100];
            multiByteOpCodes = new OpCode[0x100];
            FieldInfo[] infoArray1 = typeof(OpCodes).GetFields();
            for (int num1 = 0; num1 < infoArray1.Length; num1++)
            {
                FieldInfo info1 = infoArray1[num1];
                if (info1.FieldType == typeof(OpCode))
                {
                    OpCode code1 = (OpCode)info1.GetValue(null);
                    ushort num2 = (ushort)code1.Value;
                    if (num2 < 0x100)
                    {
                        singleByteOpCodes[(int)num2] = code1;
                    }
                    else
                    {
                        if ((num2 & 0xff00) != 0xfe00)
                        {
                            throw new Exception("Invalid OpCode.");
                        }
                        multiByteOpCodes[num2 & 0xff] = code1;
                    }
                }
            }
        }
        /// <summary>
        /// Retrieve the friendly name of a type
        /// </summary>
        /// <param name="typeName">
        /// The complete name to the type
        /// </param>
        /// <returns>
        /// The simplified name of the type (i.e. "int" instead f System.Int32)
        /// </returns>
        public static string ProcessSpecialTypes(string typeName)
        {
            string result = typeName;
            switch (typeName)
            {
                case "System.string":
                case "System.String":
                case "String":
                    result = "string"; break;
                case "System.Int32":
                case "Int":
                case "Int32":
                    result = "int"; break;
            }
            return result;
        }

        //public static string SpaceGenerator(int count)
        //{
        //    string result = "";
        //    for (int i = 0; i < count; i++) result += " ";
        //    return result;
        //}

        //public static string AddBeginSpaces(string source, int count)
        //{
        //    string[] elems = source.Split('\n');
        //    string result = "";
        //    for (int i = 0; i < elems.Length; i++)
        //    {
        //        result += SpaceGenerator(count) + elems[i] + "\n";
        //    }
        //    return result;
        //}
    }
    class Program
    {
        static void Main(string[] args)
        {
            GlobalStatic.LoadOpcode();

            Assembly asm = Assembly.LoadFile(@"C:\HJM\bitAPI\c#\CSharp\SunCraft\bin\Debug\SunCraft.exe");
            // 메소드 내용 있는거 저장용
            List<MethodInfo> limethod = new List<MethodInfo>();

            Console.WriteLine(asm.Location);
            Module[] Modules = asm.GetModules();
            #region 메소드 불러오기
            foreach (Module item in Modules)
            {
                
                Console.WriteLine("-" + item.ToString());
                Type[] types = item.GetTypes();
                foreach (Type Class in types)
                {
                    Console.WriteLine("======");
                    Console.WriteLine("--" + Class.ToString());

                    #region 클래스 내부 모든 멤버들
                    //MemberInfo[] members= Class.GetMembers(BindingFlags.NonPublic | BindingFlags.Public);
                    //foreach (MemberInfo member in members)
                    //{
                    //    //Console.WriteLine("---[member]:" + member.Name);
                    //}
                    #endregion

                    MethodInfo[] methods = Class.GetMethods(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance | BindingFlags.DeclaredOnly);
                    foreach (MethodInfo method in methods)
                    {
                        limethod.Add(method);

                        Console.Write("---[method]:" + method.Name);
                        #region 파라미터
                        //ParameterInfo[] parameters = method.GetParameters();

                        //foreach (ParameterInfo parameter in parameters)
                        //{
                        //    Console.Write(parameter.Name+",");

                        //}
                        //Console.WriteLine("");
                        #endregion

                    }
                    FieldInfo[] fields = Class.GetFields();
                    foreach (FieldInfo field in fields)
                    {
                        //Console.WriteLine("---[field]:" + field.Name);
                    }

                }
            }
            #endregion


            ILCodeReader reader;
            foreach (MethodInfo method in limethod)
            {
                
                List<OpCode> codes = new List<OpCode>();
                int position = 0;

                Console.WriteLine(method.Name+"code");
                //코드 보기
                if (method.GetMethodBody() == null)
                    continue;
                byte[] ilcodes = method.GetMethodBody().GetILAsByteArray();

                reader = new ILCodeReader(Modules[0], ilcodes);

                foreach (ILInstruct ilin in reader.m_ILInstructs)
                {
                    Console.Write(ilin.Opcode.Name);
                    if (ilin.Operand != null)
                        Console.WriteLine(", operand: " + ilin.Operand.ToString());
                    else
                        Console.WriteLine("");
                }
                /*
                int a;
                string str;
                for (position = 0; position < ilcodes.Length - 1; )
                {
                    a = 0;
                    str = null;
                    OpCode opcode = OpCodes.Nop;
                    ushort value = ilcodes[position++];

                    if (value != 0xfe)
                    {
                        opcode = Globals.singleByteOpCodes[(int)value];
                    }
                    else
                    {
                        value = ilcodes[position++];
                        opcode = Globals.multiByteOpCodes[(int)value];
                        value = (ushort)(value | 0xfe00);
                    }
                    Console.WriteLine("IL_" + position + ":" + value + ":" + opcode.Name);
                    codes.Add(opcode);

                    if (opcode.OperandType == OperandType.InlineString)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                        str = Modules[0].ResolveString(a);
                    }
                    else if (opcode.OperandType == OperandType.InlineBrTarget)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineField)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineI)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineI8)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));

                    }
                    else if (opcode.OperandType == OperandType.InlineMethod)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineNone)
                    {
                        a = 0;
                    }
                    else if (opcode.OperandType == OperandType.InlineR)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineSig)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineSwitch)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineTok)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineType)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.InlineVar)
                    {
                        a = (ilcodes[position++] | (ilcodes[position++] << 8));
                    }
                    else if (opcode.OperandType == OperandType.ShortInlineBrTarget)
                    {
                        a = ilcodes[position++];
                    }
                    else if (opcode.OperandType == OperandType.ShortInlineI)
                    {
                        a = ilcodes[position++];
                    }
                    else if (opcode.OperandType == OperandType.ShortInlineR)
                    {
                        a = (((ilcodes[position++] | (ilcodes[position++] << 8)) |
                        (ilcodes[position++] << 0x10)) | (ilcodes[position++] << 0x18));
                    }
                    else if (opcode.OperandType == OperandType.ShortInlineVar)
                    {
                        a = ilcodes[position++];
                    }
                    Console.WriteLine("operand: " + str);
                }
                Console.WriteLine("\n");
                */
                

                
                
            }

        }
    }
}
