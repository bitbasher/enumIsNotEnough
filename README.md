# When enum Just Isn't Enough: Enumeration Classes for C++
by Yves Meynard

## Accessing Resources through Symbolic Constants
If you're writing even a moderately ambitious application, you will find that it needs to access many resources of various types, for example sounds and text messages. In a large application, indiv[...] Assume that you're working on a game, which uses pre-rendered graphics, player messages, and sound effects. High-level functions allow you to write PlaySound(1001); and DisplaySprite(435);, but [...]The traditional solution to this lack of type-safety is to group your constants inside enums. Given an enum for sounds, e_Sounds, and one for sprites, e_Sprites, you can declare a function to [...] 

## numerations Don't Always Fit the Bill
You might feel this is the best you can do, and all that needs to be done. But the enum-based approach is still insufficient for serious applications. The problem is that enum is an unintelligen[...] Now it is possible to iterate over enum, so you might think that the first test, at least, is trivial: just write a for loop. Listing 1 illustrates this ideal situation. Real-world programs d[...] Using straightforward iteration with ints over an enumeration that is not continuous is legal C++; it just gives erroneous results: intermediate, "nameless" values are legal even though they are [...] Suppose you've managed to write an operator++ for a discontinuous enum — a tedious and error-prone task in the first place. Even then, maintenance issues are still a nightmare: if someone ad[...] Even if you ignore these difficulties, the second test you wanted to run remains infeasible: you still cannot tell whether a given value is a valid part of an enumeration or not. You could of cour[...] 

## An Industrial-Strength Solution
What you need is an intelligent enumeration: one that knows its minimum and maximum and its valid ranges. Such an enumeration will allow you to iterate over it automatically, because it will furni[...] The basic idea is to make each constant of your enum be a class-static constant instance of a class. This class will keep a sorted list of its own instances in a class-static container; STL's s[...] There is a potential thorn in your side: it's crucially important that it be impossible to add to the enumeration during the course of the program. However, you may want to have local variables of[...] I've made use of templates for implementing this design, since you'll typically use more than one such enumeration class. This template is meant to be used with the well-known idiom (which as far [...] Listing 3 presents a class template that implements the desired features. The class has a private: constructor from int. Only the class-static instances may be defined this way. The copy const[...] What may not be so intuitive are the two structs in the private section, Enum_Predicate_Corresponds and Enum_Ptr_Less. The first is a predicate for use with find_if in the Corresponding_Enu[...] Listing 4 gives an example of how the "enumeration class" may be used in a simple test driver. This code was compiled and run on Metrowerks CodeWarrior 7.

## Advantages and Drawbacks
Enumeration classes have the following advantages over enums: you can programmatically access their minimum and maximum values, test whether a given int is a valid enumeration constant, and ite[...] Enumeration classes do have some drawbacks: for one, they are more verbose to define (but not to use) than enums. For another, they cannot be used directly in a switch statement, although you can[...] Keep in mind, however, that enumeration classes are not meant to blindly replace all enums in existing code, but rather to replace those that correspond to collections of related constants rather[...] 

Generalization: Why Limit Yourself to ints?
What if you refer to resources using something more sophisticated than a dumb int? What use is an enumeration class when your sound-playing code reads PlaySound("Phaser1");? Well, in fact, an en[...] A generalized enumeration class is templated on its underlying type. Listing 5 provides such a class and Listing 6 gives a sample testing program together with its output. The generalization i[...] If the underlying type does not have an operator< (or if this operator doesn't do what you want), you can still use an enumeration class, but you will have to generalize still further, with a th[...] 

## Conclusion
Enumeration classes enable the encapsulation of collections of related constants. They allow programmatic access to the minimum and maximum values of the collection as well as straightforward iter[...] 

## Bibliography
[1] Bjarne Stroustrup. The C++ Programming Language, 3d Edition, (Addison-Wesley, 2000), p. 265.
[2] Scott Meyers. Effective STL (Addison-Wesley, 2001), Item 20, p. 88.

## Download the Code
<meynard.zip> (2025 – ftp site is by login only)

### About the Author
Yves Meynard has a Ph.D. in Computer Science (Operational Research) from the Université de Montréal. He holds the post of Software Analyst at SNC Lavalin Energy Control Systems. His areas of in[...]