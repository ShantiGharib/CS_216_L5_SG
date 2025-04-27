**4/27/2025**
*  **feedback.md is for instructor use only. DO NOT change the feedback.md**; make a copy if needed
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary
* what if numbers change? if it is not 1 or 0 make it const; in case of ASCII values, use chars, e.g., temp>’a’  -2
* output formatting; prompts; user friendliness; does not show  details of indvidual battles; to total health is not dispayed -5 
* 653: sort is slow as it is, why make it even slower by introducing unnecessary statements? -2
* too much empty vertical white space/blank lines reduces readability and requires more time to scroll; in general, one blank is enough between logical units -1
*  ListNode* left{nullptr}; VS. *  ListNode* left=nullptr;  two symbols {}  instead of one =; nullptr is crowded by {} which reduces readability 
* if a case in the switch has more than two statements make it a function -1
* 
* poor Id(s)  and/or inconsistent naming convention; ids should be self-documenting and as short as possible; use verbs for functions and nouns for variables; use camel-casing for variables (errorMessage) enum & const should be in upper case with words separated by “_”, e.g., MAX_TERMS, PRINT_RECORDS; pointer variables should start with p( if single)  or pp( if double pointer); flags isValid ( clearly what true would mean); if copying – e.g rhsQueue or scrQueue ; do not use IDs that are same as or very similar to C++  keywords and functions; no need to call an array “array”- it is obvious -2 -1
```text
    void AddElement(const Creature &creature);
 bool isInversion{false};
```
* 378 should be a separate function -1

