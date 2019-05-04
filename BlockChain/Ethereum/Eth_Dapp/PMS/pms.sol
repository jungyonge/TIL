pragma solidity ^0.4.19;
library SafeMath
{
    function mul(uint256 a, uint256 b) internal pure returns (uint256)
    {
        uint256 c = a * b;
        assert(a == 0 || c / a == b);

        return c;
    }

    function div(uint256 a, uint256 b) internal pure returns (uint256)
    {
        uint256 c = a / b;

        return c;
    }

    function sub(uint256 a, uint256 b) internal pure returns (uint256)
    {
        assert(b <= a);

        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256)
    {
        uint256 c = a + b;
        assert(c >= a);

        return c;
    }
}

    contract Owned {
        address public owner;

        function Owned() public {
            owner = msg.sender;
        }

        modifier onlyOwner {
            require(msg.sender == owner);
            _;
        }
        

        function transferOwnership(address _newOwner) onlyOwner public {
            owner = _newOwner;
        }          
    }
    
    contract ERC20Interface
{
    event Transfer( address indexed _from, address indexed _to, uint _value);
    function transfer( address _to, uint _value) public returns (bool _success);
}


contract PartTime is Owned,ERC20Interface {
     uint payment = 1 ether;
     using SafeMath for uint;

    struct Worker {
      string name;
      uint hour;
      uint payment;
      uint password;
      address addr;
      uint starttime;
      uint endtime;

    }
        struct Worker1{
      string name;


    }
    
    modifier checkPassword(uint _id,uint _password) {
    require(workers[_id].password == _password);
    _;
  }
    
    Worker[] public workers;
    
    
    
    mapping (uint => string) public workerOfname;
    mapping (address => uint) internal balances;
   
     function _createWorker(string _name,  uint _payment,uint _password, address _addr) onlyOwner returns (uint) {
         
        uint id = workers.push(Worker(_name, 0, _payment,_password,_addr,0,0))-1;
        
       
        workerOfname[id] = _name;
        
        return id;
      
    }

 


    
    function _startWork(uint _id,uint _password) {
        require(workers[_id].password == _password);
        require(workers[_id].addr == msg.sender);
        workers[_id].starttime = block.timestamp;
        
    }
    
    function _endWork(uint _id,uint _password) {
        require(workers[_id].password == _password);
        require(workers[_id].addr == msg.sender);
        workers[_id].endtime = block.timestamp;
        uint _hour = (workers[_id].endtime .sub(workers[_id].starttime)).div(3600).add(300);
        
        _addHour(_id,_hour);
        
    }
    function _getHour(uint _id, uint _password) view returns (uint) {

      
    return workers[_id].hour;
    }
    
    function _addHour(uint _id,uint _hour) {
    workers[_id].hour= workers[_id].hour .add(_hour);
    workers[_id].endtime = workers[_id].starttime = 0;
    }
    
    function _subHour(uint _id,uint _hour) onlyOwner {
    workers[_id].hour= workers[_id].hour.sub(_hour);
    }
    
    function _chgPayment(uint _id,uint32 _payment) onlyOwner {
    workers[_id].payment= _payment;
    }
    
    
    function _withdrawPay(uint _id, address _to) public payable 
    {
     require(workers[_id].addr == _to);
     uint _value = (workers[_id].hour.mul(workers[_id].payment)).mul(payment);
    
        transfer( _to, _value);
        workers[_id].hour = 0 ;
      
    }
    
    function _depositMoney() payable returns(bool success) {
        balances[msg.sender] = balances[msg.sender] .add(msg.value);

        return true;
    }
    
    
    function transfer(address _to, uint _value) public returns (bool) 
    {
        require(balances[msg.sender] >= _value);
      
        balances[msg.sender] = balances[msg.sender]-(_value);
        _to.transfer(_value);
        
        Transfer(msg.sender, _to, _value);
        
        return true;
    }
    
    

}
