## XUI
  XUI is a C++20 library for building user interfaces.
  
### Usage
```cpp
xui::init ( window , [ ] ( ) { 
        auto form = xui::begin_form ( "Form" , { 300U , 400U } ); {

          form->add_child ( std::move ( xui::make_page ( "Page" ) ) );

        }; xui::end_form ( std::move ( form ) );
      } );
```

## Requirements
XUI works with a C++20 compiler, requires no additional dependencies, include `<xui/xui.hpp>` and you're ready to start.
