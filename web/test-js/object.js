'use strict';

// 普通方法
function createNewPerson(name){
    let obj = {};
    obj.name = name;
    obj.greeting = function(){
        console.log('Hi! I\'m ' + this.name + '.');
    };
    return obj;
}

let salva = createNewPerson('salva');
salva.name;
salva.greeting();

/*
 * 改进1： 使用构建函数
 * 直接使用this，不需要let obj, return obj;
 * 构建函数的头字母大写，区别普通函数；
 * 调用构建函数，使用 new 方法；
 */
function Person(name){
    this.name = name;
    this.greeting = function(){
        console.log('Hi! I\'m ' + this.name + '.');
    };
}

let bob = new Person('Bob');
let sarah = new Person('Sarah');

bob.greeting();
sarah.greeting();

/*
 * 改进2： 完整版
 */
function Person2(first, last, age, gender, interests){
    this.name = {
        first,
        last
    };
    this.age = age;
    this.gender = gender;
    this.interests = interests;
    this.bio = function() {
        console.log(this.name.first + ' ' + this.name.last + ' is ' + this.age + ' years old. He likes ' + this.interests[0] + ' and ' + this.interests[1] + '.');
    };
    this.greeting = function() {
      console.log('Hi! I\'m ' + this.name.first + '.');
  };
}

let bob_smith = new Person2('Bob', 'Smith', 32, 'male', ['music', 'skiing']);
bob_smith.bio();

/*
  扩展 ：Object() 构造函数
*/
let obj_person = new Object();
obj_person.name = 'Chris';
obj_person['age'] = 38;
obj_person.geeeting = function(){
    console.log('I am ' + this.name + '.');
};

let obj_person1 = new Object({
    name : 'Obj1',
    age : 38,
    greeting : function(){
        console.log('I am ' + this.name + '.');
    }
});

/*
  扩展 create(), 从原型构造一个新对象实例
*/
let c_person = Object.create(obj_person1);
c_person.name = 'created_person';
c_person.greeting();
obj_person1.greeting();

/*
  prototype-based language
  prototype-chain 用于继承方式，属性
*/
console.log(Object.getPrototypeOf(c_person));
//{ name: 'Obj1', age: 38, greeting: [Function: greeting] }
console.log(c_person.__proto__);
//{ name: 'Obj1', age: 38, greeting: [Function: greeting] }
console.log(c_person.prototype); //undefined

let doSomething = function(){};
console.log(doSomething.prototype); // 函数的原型属性
// doSomething {}
console.log(doSomething.__proto__);
// [Function]
console.log(Object.getPrototypeOf(doSomething));
// [Function]

function doAgain(){}
console.log(doAgain.prototype);
// doAgain(){}

doSomething.prototype.foo = "bar";
console.log(doSomething.prototype); // 函数的原型属性

let doSomething1 = new doSomething();
doSomething1.prop = 'some value';
console.log(doSomething1);
console.log(doSomething1.prototype);
console.log(doSomething1.__proto__);

console.log("doSomeInstancing.prop:      " + doSomething1.prop);
console.log("doSomeInstancing.foo:       " + doSomething1.foo);
console.log("doSomething.prop:           " + doSomething.prop);
console.log("doSomething.foo:            " + doSomething.foo);
console.log("doSomething.prototype.prop: " + doSomething.prototype.prop);
console.log("doSomething.prototype.foo:  " + doSomething.prototype.foo);
/*
doSomeInstancing.prop:      some value
doSomeInstancing.foo:       bar
doSomething.prop:           undefined
doSomething.foo:            undefined
doSomething.prototype.prop: undefined
doSomething.prototype.foo:  bar
*/

//================================================================================
// constructor

console.log(c_person.constructor);
let c_person1 = new bob_smith.constructor('Bob1', 'Smith1', 32, 'male', ['music', 'skiing']);
c_person1.bio();
console.log(bob_smith.constructor.name);
console.log(c_person1.constructor.name);

Person2.prototype.farewell = function(){
    console.log(this.name.first + ' bye!');
};

c_person1.farewell();
bob_smith.farewell();


/*
 * 改进3： 分离属性和方法定义
 *  在构造函数内定义属性；
 *  在prototype中定义方法，全局属性；
 */
function Test(a,b,c){
    this.a = a;
    this.b = b;
    this.c = c;
}

Test.prototype.getA = function(){
    console.log('test.getA()');
    return this.a + 1;
};

let test = new Test(1,2,3);
console.log(test.getA());

/* 改进4：继承
    super.call(this, ...);// 添加新属性
    sub.prototype = Object.create(super.prototype); // 继承方法
 */
// Person3
function Person3(first, last, age, gender, interests){
    this.name = {
        first,
        last
    };
    this.age = age;
    this.gender = gender;
    this.interests = interests;
}

Person3.prototype.bio = function() {
    console.log(this.name.first + ' ' + this.name.last + ' is ' + this.age + ' years old. He likes ' + this.interests[0] + ' and ' + this.interests[1] + '.');
};
Person3.prototype.greeting = function() {
    console.log('Hi! I\'m ' + this.name.first + '.');
};

let person4 = new Person3('p4-first', 'p4-last', 28, 'male', ['teacher', 'sleep']);
person4.bio();

// 定义之类
function Teacher(first, last, age, gender, interests, subject) {
  Person3.call(this, first, last, age, gender, interests);

  this.subject = subject;
}
// 重点*** 继承原型, 修改原型构造函数
Teacher.prototype = Object.create(Person3.prototype);
Teacher.prototype.constructor = Teacher;
// 重写继承方法
Teacher.prototype.greeting = function(){
    console.log('I am teacher ' + this.name.first + '.'+ this.name.last);
};

let teacher = new Teacher('first-t', 'last-t', 28, 'male', ['teacher', 'english'], 'english');
teacher.bio();
teacher.greeting();
bob_smith.greeting();