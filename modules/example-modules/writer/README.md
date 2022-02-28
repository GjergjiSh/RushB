# Reader Example

Simple Module that just sets the servo values in the data shared between the modules to a configured value

# Usage

* Build by running `make`
* Copy `Writer.so` in the Control Center's `bin/modules` folder
* Add the following to the Control Center's `bin/Modules.xml` file

~~~xml
<module name="Writer">
    <parameters>
        <parameter name="TOP_SERVO" value="10" />
        <parameter name="LEFT_SERVO" value="20" />
        <parameter name="RIGHT_SERVO" value="30" />
    </parameters>
</module>
~~~

* Run the Control Center

You should see `Reader says Hello World` printed in the console during the initialization step and the values
for the configured value for the servos should be set during the cycle step. Use the provided example `Reader`
module to print them.