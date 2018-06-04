# `<ehl/safe_type.h>`

Provides safe types with developer specifed invariants that can easily replace
built in types. Safe types cannot be implicitly converted to each other even if
their underlying types are the same, unlike built in types.

## Usage

### `ehl::safe_type<underlying, tag, operations...>`

This template provides a simple template for creating a safe type without any
advanced functionality. 

Template parameters:

* `underlying` - the type to be wrapped by the safe type.
* `tag` - a tag type to make type unique. If the type you are creating is
  called `xyz_t` then specify this as `struct xyz_t_tag`. (Note the type only
  needs to be declared not defined) 
* `operations...` - a list of operation templates that describe what operations
  the type supports. See [operations](#operations) section below 

#### Examples

```
#include &lt;ehl/safe_type.h&gt;

using id_t = ehl::safe_type&lt;unsigned int, struct id_t_tag&gt;;

id_t myIdentification{10};

```

This code creates a type called `id_t` using an `unsigned int` as its
underlying type and then instantiates an instance of `id_t` called
`myIdentification`.

### `ehl::extendable_safe_type<underlying, derived, operations...>`

This template provides a simple template for creating a safe type by
inheriting from it, allowing additional custom behaviors to be added to the
type.


Template parameters:

* `underlying` - the type to be wrapped by the safe type.
* `derived` - the type of the class using this type as a base class. 
* `operations...` - a list of operation templates that describe what operations
  the type supports. See [operations](#operations) section below 

#### Examples

```
#include &lt;ehl/safe_type.h&gt;

class id_t : public ehl::extendable_safe_type&lt;unsigned int, id_t&gt;
{
    // Import the constructors from the base class
    using ehl::extendable_safe_type&lt;unsigned int, id_t&gt;::extendable_safe_type;
    
    void additional_behavior();
};

id_t myIdentification{10};

```

This code creates a type called `id_t` using an `unsigned int` as its
underlying type and then instantiates an instance of `id_t` called
`myIdentification`.


<a name="operations"></a>
## Operations Usage

Operations add behaviors to a safe type.

### `ehl::safe_type_operation::add`

Adds the binary `+` operator for the type.

#### Examples

```
#include &lt;ehl/safe_type.h&gt;

using addable_t = ehl::safe_type&lt;unsigned int, struct addable_t_tag,
    ehl::safe_type_operation::add&gt;;

addable_t a{10};
addable_t a{15};

addable_t c = a + b;

```

### `ehl::safe_type_operation::subtract`

Adds the binary `-` operator for the type.

#### Examples

```
#include &lt;ehl/safe_type.h&gt;

using addable_t = ehl::safe_type&lt;unsigned int, struct addable_t_tag,
    ehl::safe_type_operation::subtract&gt;;

addable_t a{10};
addable_t a{15};

addable_t c = a - b;

```
