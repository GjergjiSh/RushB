# Reader Example

Simple Module that just reads the servo values from the data shared between the modules

# Usage

* Build by running `make`
* Copy `Reader.so` in the Control Center's `bin/modules` folder
* Add the following to the Control Center's `bin/Modules.xml` file

~~~xml
<module name="Reader">
    <parameters>
        <parameter name="HELLO" value="Reader says Hello World :)" />
    </parameters>
</module>
~~~

* Run the Control Center

You should see `Reader says Hello World` printed in the console during the initialization step and the values
for the servos being printed during the cycle step