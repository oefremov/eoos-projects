/** 
 * Entry point to an operating system main program.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Program.hpp"
#include "library.String.hpp"

namespace local
{
    namespace unit
    {
        /**
         * @param L maximum number of string characters, or 0 for dynamic allocation.
         */
        template <int32 L> 
        class StringTest : public Object<Allocator>
        {
            typedef char                           T;
            typedef Allocator                      A;
            typedef Object<A>                      Parent; 
            typedef library::String<T,L,A>         String; 
            typedef api::String<T>                 IString;         
    
        public:
        
            /** 
             * Constructor.
             */    
            StringTest() : Parent()
            {
                bool isConstructed = construct(); 
                this->setConstruct( isConstructed );            
            }     
            
            /**
             * Destructor.
             */
            virtual ~StringTest()
            {
            }
            
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */    
            bool isConstructed() const
            {
                return Parent::getConstruct();
            }        
            
            /**
            * Executes tests.
            *
            * @return true if the tests has been completed successfully.
            */
            virtual bool execute()
            {
                if( not this->isConstructed() )
                {
                    return false;
                }

                if( not testConstructors() )       
                {
                    return false;            
                }  
                    
                if( not testInterfaces() )       
                {
                    return false;            
                }              
                
                if( not testOperators() )       
                {
                    return false;            
                }

                if( not testNumbers() )       
                {
                    return false;            
                }            

                return true;
            }
    
        private:  
        
            /**
            * Tests all the constructors is avaliable.
            *
            * @return true if the test has been completed successfully.
            */
            bool testConstructors()
            {
                // Test that the DEFAULT CONSTRUCTOR is avaliable
                String s0;
                if( not s0.isConstructed() )
                {
                    return false;
                }
                // Test that the CONSTRUCTOR with A SOURCE CHARACTER STRING argument is avaliable
                String s1( "Hello, world!" );
                if( not s1.isConstructed() )
                {
                    return false;
                }            
                // Test that the COPY CONSTRUCTOR with A SOURCE OBJECT argument is avaliable
                String s2( s1 );
                if( not s2.isConstructed() )
                {
                    return false;
                }
                // Test that the CONSTRUCTOR with A SOURCE OBJECT INTERFACE argument is avaliable
                IString& is = s1;
                String s3( is );
                if( not s3.isConstructed() )
                {
                    return false;
                }                                    
                
                // Test that the CONSTRUCTOR with A SOURCE INT32 NUMBER argument is avaliable
                int32 i32 = 0x12345;
                String s4( i32 );
                if( not s4.isConstructed() )
                {
                    return false;
                }
                
                return true;
            }  
        
            /**
            * Tests all the interfaces is avaliable.
            *
            * @return true if the test has been completed successfully.
            */
            bool testInterfaces()
            {
                // The 13 character string
                const Context c1("Hello, world!");               
                        
                // The 6 character string
                const Context c2("Hello.");             
                    
                // The 12 character string            
                const Context c3("How are you?"); 
                
                // The 18 character string            
                const Context c4("Hello.How are you?");             
                
                // Check base built string
                if( not isInterfaces( c1.inf, c1.len ) )
                {
                    return false;            
                }
                
                // Check copied string
                if( not c1.inf.copy(c2.inf) )
                {
                    return false;
                }
                if( not isInterfaces(c1.inf, c2.len) )
                {
                    return false;            
                }
                
                // Check concatenated string
                if( not c1.inf.concatenate(c3.inf) )
                {
                    return false;
                }
                if( not isInterfaces(c1.inf, c2.len + c3.len) )
                {
                    return false;            
                }   
                
                // Check comparation
                if( c1.inf.compare(c4.inf) != 0 )
                {
                    return false;
                }            
                            
                return true;        
            }
            
            /**
            * Tests all the interfaces is avaliable.
            *
            * @return true if the test has been completed successfully.
            */
            bool isInterfaces(const IString& is, int32 length)
            {
                if( not is.isConstructed() )
                {
                    return false;
                }
                if( is.getLength() != length )
                {
                    return false;
                }            
                if( is.isEmpty() )
                {
                    return false;
                }    
                if( is.getChar() == NULL )
                {
                    return false;
                }                
                return true;            
            }
            
            /**
            * Tests all the operators is avaliable.
            *
            * @return true if the test has been completed successfully.
            */
            bool testOperators()
            {
                // The 13 character string
                const Context c1("Hello, world!");
                // The 13 character string
                const Context c2("Hello, world!");            
                // The 13 character string
                const Context c3("Hello,      !");
                // The 14 character string
                const Context c4("Hello, people!");
                
                // Test operator = 
                if( not assignmentOperator< T* >(c1.str, c1.len) )
                {
                    return false;
                }
                if( not assignmentOperator< String >(c1.obj, c1.len) )
                {
                    return false;
                }            
                if( not assignmentOperator< IString& >(c1.inf, c1.len) )
                {
                    return false;
                }  
                // Test operator += 
                if( not assignmentBySumOperator< T* >(c1.str, c1.len) )
                {
                    return false;
                }
                if( not assignmentBySumOperator< String >(c1.obj, c1.len) )
                {
                    return false;
                }            
                if( not assignmentBySumOperator< IString& >(c1.inf, c1.len) )
                {
                    return false;
                }
                
                // Test operator ==             
                if( not equalToOperator< String, String >(c1.obj, c2.obj) )
                {
                    return false;
                }
                if( not equalToOperator< String, IString& >(c1.obj, c2.inf) )
                {
                    return false;
                }            
                if( not equalToOperator< IString&, String >(c1.inf, c2.obj) )
                {
                    return false;
                } 
                if( not equalToOperator< String, T* >(c1.obj, c2.str) )
                {
                    return false;
                }                        
                if( not equalToOperator< T*, String >(c1.str, c2.obj) )
                {
                    return false;
                }
    
                // Test operator !=  
                if( not notEqualToOperator< String, String >(c1.obj, c3.obj) )
                {
                    return false;
                }
                if( not notEqualToOperator< String, IString& >(c1.obj, c3.inf) )
                {
                    return false;
                }            
                if( not notEqualToOperator< IString&, String >(c1.inf, c3.obj) )
                {
                    return false;
                } 
                if( not notEqualToOperator< String, T* >(c1.obj, c3.str) )
                {
                    return false;
                }                        
                if( not notEqualToOperator< T*, String >(c1.str, c3.obj) )
                {
                    return false;
                } 
                
                // Test operator +  
                if( not concatenateOperator< String, String >(c1.obj, c4.obj, c1.len, c4.len) )
                {
                    return false;
                }
                if( not concatenateOperator< String, IString& >(c1.obj, c4.inf, c1.len, c4.len) )
                {
                    return false;
                }            
                if( not concatenateOperator< IString&, String >(c1.inf, c4.obj, c1.len, c4.len) )
                {
                    return false;
                } 
                if( not concatenateOperator< String, T* >(c1.obj, c4.str, c1.len, c4.len) )
                {
                    return false;
                }                        
                if( not concatenateOperator< T*, String >(c1.str, c4.obj, c1.len, c4.len) )
                {
                    return false;
                }                   
                return true;        
            }  
            
            /**
            * Tests an operator =.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename T>
            bool assignmentOperator(const T str, int32 len)
            {
                String s("Test!");
                s = str;
                return s.getLength() == len ? true : false;
            }
            
            /**
            * Tests an operator +=.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename T>
            bool assignmentBySumOperator(const T str, int32 len)
            {
                const int32 S_LENGTH = 5;          
                String s("Test!");
                s += str;
                return s.getLength() == len + S_LENGTH ? true : false;
            }        
            
            /**
            * Tests an operator ==.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename T1, typename T2>
            bool equalToOperator(const T1 str1, const T2 str2)
            {
                return str1 == str2 ? true : false;
            }        
            
            /**
            * Tests an operator !=.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename T1, typename T2>
            bool notEqualToOperator(const T1 str1, const T2 str2)
            {
                return str1 != str2 ? true : false;
            }  
            
            /**
            * Tests an operator +.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename T1, typename T2>
            bool concatenateOperator(const T1 str1, const T2 str2, int32 len1, int32 len2)
            {
                String s;
                s = str1 + str2;
                return s.getLength() == len1 + len2 ? true : false;
            }
            
            /**
            * Tests all the operators is avaliable.
            *
            * @return true if the test has been completed successfully.
            */
            bool testNumbers()
            {  
                // Test implicitly casting
                if( not castNumberByConstructor<int32,T*>(-2147483647, "-2147483647") )
                {
                    return false;
                }
                // NOTE: The int64 T is excluded from the string class
                //if( not castNumberByConstructor<int64,T*>(-9223372036854775807, "-9223372036854775807") )
                //{
                //    return false;
                //}             
                // Test min available int32 value
                if( not castNumber<int32>(-2147483647) )
                {
                    return false;
                }
                // Test min unavailable int32 value
                if( castNumber<int32>(-2147483648) )
                {
                    return false;
                }
                // Test uint32 value            
                if( not castNumber<uint32>(0xffffffff) )
                {
                    return false;
                }
                // NOTE: The int64 T is excluded from the string class                        
                // Test min available int64 value
                //if( not castNumber<int64>(-9223372036854775807) )
                //{
                //    return false;
                //}
                // Test min unavailable int64 value
                //if( castNumber<int64>(-9223372036854775808) )
                //{
                //    return false;
                //} 
                // Test uint64 value
                //if( not castNumber<uint64>(0xffffffffffffffff) )
                //{
                //    return false;
                //}
                return true;     
            }
            
            /**
            * Tests casting interface.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename I, typename S>
            bool castNumberByConstructor(const I value, const S string)
            {
                String str(value);
                if(str != string)
                {
                    return false;
                }
                I cast = str;
                return value == cast ? true : false;        
            }        
            
            /**
            * Tests casting interface.
            *
            * @return true if the test has been completed successfully.
            */        
            template <typename I>
            bool castNumber(const I value, int32 base = 10)
            {
                String str;
                if( not str.template convert<I>(value) )
                {
                    return false;
                }
                I cast = str.template cast<I>();
                return value == cast ? true : false;
            }              
        
            /** 
            * Constructor.
            *
            * @return true if object has been constructed successfully.
            */
            bool construct()
            {
                if( not this->isConstructed() )
                {
                    return false;
                }
                return true;
            }
            
            /** 
            * Context for test.
            */        
            struct Context
            {
                /** 
                * Constructor.
                */        
                Context(T* string) :
                    str (string),
                    obj (str),
                    inf (obj),
                    len (obj.getLength()){
                }
                
                /**
                * Destructor.
                */
            ~Context()
                {
                }
                
                /**
                * A source character string.         
                */               
                T* str;
    
                /**
                * A source object.         
                */             
                String obj;
                
                /**
                * A source object interface.         
                */             
                IString& inf;
    
                /**
                * A source string length.         
                */                  
                int32 len;
    
            };
            
        };
    }
    
    /**
    * Starts executing an operating system main program.
    *
    * @return zero, or error code if an error has been occurred.
    */
    int32 Program::start()
    {
        // Test the char type partial specialization of the static string class.
        unit::StringTest<100> staticStringTest;
        if( not staticStringTest.execute() )
        {
            return -1;
        } 
        // Test the char type partial specialization of the dynamic string class.
        unit::StringTest<0> dynamicStringTest;
        if( not dynamicStringTest.execute() )
        {
            return -1;
        } 
        return 0; 
    }
}
