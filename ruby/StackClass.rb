#defines and tests a stack of maximum length 100,implemented in an arrry
 
class StackClass
    
    #Constructor

    def initialize
        @stackRef = Array.new
        @maxLen = 100
        @topIndex = -1
    end

    #push method
    
    def push(number)
        if @topIndex == @maxLen
            puts "Error in push - stack is full"
        else
            @topIndex = @topIndex + 1
            @stackRef[@topIndex] = number
        end
    end

    # pop method
    
    def pop
        if @topIndex == -1
            puts"Error in pop - stack is empty"
        else
            @topIndex = @topIndex -1
        end
    end

    #top method

    def top 
        @stackRef[@topIndex]
    end

    #empty method

    def empty
        @topIndex == -1
    end

end #end of Stack class

myStack = StackClass.new
myStack.push(100)
myStack.push(200)
puts "Top element is (should be 200): #{myStack.top}"

myStack.pop
puts "Top element is (should be 100): #{myStack.top}"

myStack.push("pig")
puts "Top element is (should be pig): #{myStack.top}"
