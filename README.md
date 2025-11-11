# When enum Just Isn't Enough: Enumeration Classes for C++
by Yves Meynard, 2003

## Accessing Resources through Symbolic Constants
If you're writing even a moderately ambitious application, you will find that it needs to access many resources of various types, for example sounds and text messages. In a large application, individual resources can easily number in the hundreds. Typically, they will be referenced by a numeric value. For the time being, I'll suppose you're using ints to refer to resources, but I'll generalize later.

Assume that you're working on a game, which uses pre-rendered graphics, player messages, and sound effects. High-level functions allow you to write PlaySound(1001); and DisplaySprite(435);, but of course you wouldn't use magic numbers. You might declare symbolic constants instead, as in const int explosionSnd = 1001;. This is definitely better, but not type-safe: nothing prevents you from writing DisplaySprite(explosionSnd); when you meant to write DisplaySprite(explosionSprite);.

The traditional solution to this lack of type-safety is to group your constants inside enums. Given an enum for sounds, e_Sounds, and one for sprites, e_Sprites, you can declare a function to take an argument of the proper type, as in void DisplaySprite(e_Sprite);. Once this has been done, the compiler will ensure that you cannot accidentally pass a sound constant to a sprite display function.

## Enumerations Don't Always Fit the Bill
You might feel this is the best you can do, and all that needs to be done. But the enum-based approach is still insufficient for serious applications. The problem is that enum is an unintelligent structure: C++ does not allow you to programmatically extract anything significant from it. This makes it impossible to automate operations on enum, when this is precisely what needs to be done for many applications. Consider that huge game with its hundreds of sounds: you'd certainly like to be able to verify that every sound constant referenced in the code corresponds to a sound that is actually available in the current version of the application. The inverse task is also important: if those 25 new sounds that were just added in the new version are never even played, you'd want your automated tests to notice that.

Now it is possible to iterate over enum, so you might think that the first test, at least, is trivial: just write a for loop. Listing 1 illustrates this ideal situation. Real-world programs do not look anything like this, however. Both initial design considerations and maintenance issues conspire to produce a situation like that in Listing 2. When you've got even one "hole" in your enum, you're in trouble.

Using straightforward iteration with ints over an enumeration that is not continuous is legal C++; it just gives erroneous results: intermediate, "nameless" values are legal even though they are meaningless. Now, since enum is a user-defined type, it is possible to define an increment/decrement operator for it [1]. This makes it possible to iterate through enum using a for loop with a specific operator++. However, this is a false solution: it can indeed be very useful for small, continuous enums — for instance, if you have an enum for the days of the week, it's very convenient to define an operator++ that always returns the next day of the week — but with a large, discontinuous enumeration things go rapidly sour.

Suppose you've managed to write an operator++ for a discontinuous enum — a tedious and error-prone task in the first place. Even then, maintenance issues are still a nightmare: if someone adds a sound constant to the e_Sounds enum in an "empty slot," your operator++ will skip right over it without warning. If this constant is somehow passed to your operator++, it will fail to recognize it and at best give a wrong result, if it doesn't cause a run-time error instead.

Even if you ignore these difficulties, the second test you wanted to run remains infeasible: you still cannot tell whether a given value is a valid part of an enumeration or not. You could of course write a custom function to do this, and then you'd suffer from the very same maintenance nightmares I was just talking about. Unless you enjoy wasting hours debugging, something better is clearly indicated.

## An Industrial-Strength Solution
What you need is an intelligent enumeration: one that knows its minimum and maximum and its valid ranges. Such an enumeration will allow you to iterate over it automatically, because it will furnish its own standard mechanism for doing so, which will obviate the need to write and maintain one yourself. In other words, you need a class that allows you to unify symbolic constants into a single type.

The basic idea is to make each constant of your enum be a class-static constant instance of a class. This class will keep a sorted list of its own instances in a class-static container; STL's std::set is ideal since it keeps its contents sorted. Iterating over the enumeration becomes a matter of iterating over the set. Since the set is sorted, it becomes trivial to obtain the enumeration's maximum and minimum. This design is proof against maintenance problems, since the set is built from the constants defined in the code: whether constants are added or removed, the set will always be correctly built.

There is a potential thorn in your side: it's crucially important that it be impossible to add to the enumeration during the course of the program. However, you may want to have local variables of the type of the enumeration, just like with regular enums. The first requirement seems to imply you can only construct class instances before main is executed, and the other requires construction during the course of the program. In fact this simply forces you to distinguish between class-static instances (constructed before main is executed from their int value, immutable) and local instances (constructed dynamically by copying from a class-static instance, mutable).

I've made use of templates for implementing this design, since you'll typically use more than one such enumeration class. This template is meant to be used with the well-known idiom (which as far as I know lacks a standard name) whereby class A is derived from a class B templated on A itself.

Listing 3 presents a class template that implements the desired features. The class has a private: constructor from int. Only the class-static instances may be defined this way. The copy constructor (synthesized by the compiler) makes it possible to instantiate local variables that are copies of class-static instances. The class keeps a set of its static instances, which is always sorted. STL thus does all the hard work for you, and your implementation can remain simple and intuitive, or nearly so.

What may not be so intuitive are the two structs in the private section, Enum_Predicate_Corresponds and Enum_Ptr_Less. The first is a predicate for use with find_if in the Corresponding_Enum method. It's not strictly necessary, since I could have used an explicit loop comparing the members of the set with the sought value, but find_if is better style. The second struct, Enum_Ptr_Less, is absolutely necessary to keep your set sorted in the order you want. As Scott Meyer points out in [2], you have to be careful when dealing with associative containers of pointers. The containers will by default be sorted by comparing the pointer values, which is almost never what you want. So you have to give the set a comparison object whose operator(), when given two members of the set, will return whether the first one is less than the other according to the appropriate criterion. In our example, you need to compare the results of the Get_Value function.
Listing 4 gives an example of how the "enumeration class" may be used in a simple test driver. This code was compiled and run on Metrowerks CodeWarrior 7.

## Advantages and Drawbacks
Enumeration classes have the following advantages over enums: you can programmatically access their minimum and maximum values, test whether a given int is a valid enumeration constant, and iterate over a given enumeration class. An enumeration class instance is never implicitly converted to an int value, although this value may be obtained explicitly. Given an int value, you can obtain the corresponding enumeration class constant, if it exists.

Enumeration classes do have some drawbacks: for one, they are more verbose to define (but not to use) than enums. For another, they cannot be used directly in a switch statement, although you can of course switch using the Get_Value function. Even though these are not major handicaps, the fact remains that using enumeration classes is less straightforward than using ordinary enums.

Keep in mind, however, that enumeration classes are not meant to blindly replace all enums in existing code, but rather to replace those that correspond to collections of related constants rather than symbolic representations of unified abstract concepts. In other words, if you're using an enum to group together the numbers of all the error messages your application uses, you should consider an enumeration class instead; but a days-of-the-week enum should remain a plain enum.

## Generalization: Why Limit Yourself to ints?
What if you refer to resources using something more sophisticated than a dumb int? What use is an enumeration class when your sound-playing code reads PlaySound("Phaser1");? Well, in fact, an enumeration class is just what you need. The basic ideas I've presented here apply just as well when the underlying enumerated type is something other than int — as long as it can be ordered (i.e., it has or can have an operator<). The benefits can be even greater, since an enumeration class always allows iteration over the underlying type even when this is impossible in the general case. In practice, this means an enumeration class enables you to iterate over every sound-resource string in your application, from "Arrakis" to "Zabulon Computation."

A generalized enumeration class is templated on its underlying type. Listing 5 provides such a class and Listing 6 gives a sample testing program together with its output. The generalization is fairly straightforward: you must add another template parameter for the underlying type, which I've called TValue. To avoid copy inefficiencies, TValue is always passed by reference to const and likewise the predicate stores a const TValue&.

If the underlying type does not have an operator< (or if this operator doesn't do what you want), you can still use an enumeration class, but you will have to generalize still further, with a third template parameter, this one a comparison object to pass to the Enum_Ptr_Less object. The details are left as an exercise for the reader.

## Conclusion
Enumeration classes enable the encapsulation of collections of related constants. They allow programmatic access to the minimum and maximum values of the collection as well as straightforward iteration and membership tests. In their simpler form, they can be viewed as an improved form of enum. By templating them on their underlying enumerated type, they can be applied to collections of constants of any ordered type.

## Bibliography
1. Bjarne Stroustrup. _The C++ Programming Language_, 3d Edition, (Addison-Wesley, 2000), p. 265.
2. Scott Meyers. _Effective STL_ (Addison-Wesley, 2001), Item 20, p. 88.

## Download the Code
<meynard.zip> (2025 – ftp site is by login only)

### About the Author
Yves Meynard has a Ph.D. in Computer Science (Operational Research) from the Université de Montréal. He holds the post of Software Analyst at SNC Lavalin Energy Control Systems. His areas of interest include optimization heuristics and code refactoring. He may be reached at ymeynard@globetrotter.net.
