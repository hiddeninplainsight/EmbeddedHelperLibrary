# `<ehl/safe_type.h>`

Provides safe types with developer specifed invariants that can easily replace
built in types. Safe types cannot be implicitly converted to each other even if
their underlying types are the same, unlike built in types.

## Usage

### `ehl::safe_type<tag, underlying, operations...>`

This template provides a simple template for creating a safe type without any
advanced functionality. 

Template parameters:

* `tag` - a tag type to make type unique. If the type you are creating is
  called `xyz_t` then specify this as `struct xyz_t_tag`. (Note the type only
  needs to be declared not defined) 
* `underlying` - the type to be wrapped by the safe type.
* `operations...` - a list of operation templates that describe what operations
  the type supports. See [operations](#operations) section below 

#### Examples

```
#include <ehl/safe_type.h>

using id_t = ehl::safe_type<struct id_t_tag, unsigned int>;

id_t myIdentification{10};
```

This code creates a type called `id_t` using an `unsigned int` as its
underlying type and then instantiates an instance of `id_t` called
`myIdentification`.

### `ehl::extendable_safe_type<derived, underlying, operations...>`

This template provides a simple template for creating a safe type by
inheriting from it, allowing additional custom behaviors to be added to the
type.


Template parameters:

* `derived` - the type of the class using this type as a base class. 
* `underlying` - the type to be wrapped by the safe type.
* `operations...` - a list of operation templates that describe what operations
  the type supports. See [operations](#operations) section below 

#### Examples

```
#include <ehl/safe_type.h>

class id_t : public ehl::extendable_safe_type<id_t, unsigned int>
{
    // Import the constructors from the base class
    using ehl::extendable_safe_type<id_t, unsigned int>::extendable_safe_type;
    
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

### Binary operations

<table>
<tr><td>operation</td><td>binary operator</td></tr>
<tr><td><code>ehl::safe_type_operation::add</code></td><td><code>+</code></td></tr>
<tr><td><code>ehl::safe_type_operation::subtract</code></td><td><code>-</code></td></tr>
<tr><td><code>ehl::safe_type_operation::multiply</code></td><td><code>*</code></td></tr>
<tr><td><code>ehl::safe_type_operation::divide</code></td><td><code>/</code></td></tr>
</table>

#### Example

```
#include <ehl/safe_type.h>

using addable_t = ehl::safe_type<struct addable_t_tag, unsigned int,
    ehl::safe_type_operation::add>;

addable_t a{10};
addable_t b{15};

addable_t c = a + b;
```

### Unary operations

<table>
<tr><td>operation</td><td>unary operator</td></tr>
<tr><td><code>ehl::safe_type_operation::preincrement</code></td><td><code>++p</code></td></tr>
<tr><td><code>ehl::safe_type_operation::postincrement</code></td><td><code>p++</code></td></tr>
</table>

#### Example

```
#include <ehl/safe_type.h>

using preincrement_t = ehl::safe_type<struct preincrement_t_tag, unsigned int,
    ehl::safe_type_operation::preincrement>;

preincrement_t a{10};

++a;
```

### Comparison operations

<table>
<tr><td>operation</td><td>comparison operator</td></tr>
<tr><td><code>ehl::safe_type_operation::equal</code></td><td><code>==</code></td></tr>
<tr><td><code>ehl::safe_type_operation::not_equal</code></td><td><code>!=</code></td></tr>
<tr><td><code>ehl::safe_type_operation::less_than</code></td><td><code>&lt;</code></td></tr>
<tr><td><code>ehl::safe_type_operation::less_than_or_equal</code></td><td><code>&lt;=</code></td></tr>
<tr><td><code>ehl::safe_type_operation::greater_than</code></td><td><code>&gt;</code></td></tr>
<tr><td><code>ehl::safe_type_operation::greater_than_or_equal</code></td><td><code>&gt;=</code></td></tr>
</table>

#### Example

```
#include <ehl/safe_type.h>

using equal_t = ehl::safe_type<struct equal_t_tag, unsigned int,
    ehl::safe_type_operation::equal>;

equal_t a{10};
equal_t b{15};

if(a == b)
{
    // ...
}
```

### Combined comparison operations

`ehl::safe_type_operation::compare` adds the following safe type operators:
* `ehl::safe_type_operation::equal`
* `ehl::safe_type_operation::notequal`
* `ehl::safe_type_operation::less_than`
* `ehl::safe_type_operation::less_than_or_equal`
* `ehl::safe_type_operation::greater_than`
* `ehl::safe_type_operation::greater_than_or_equal`

### Conversion operation

`ehl::safe_type_operation::implicitly_convert_to<typename U>::operation` adds the `operator U()` method to the type.

#### Example

```
#include <ehl/safe_type.h>

using convertable_to_t = ehl::safe_type<struct convertable_to_t_tag, unsigned int,
    ehl::safe_type_operation::implicitly_convert_to<long>::operation>;

convertable_to_t a{10};
long b = a;
```
