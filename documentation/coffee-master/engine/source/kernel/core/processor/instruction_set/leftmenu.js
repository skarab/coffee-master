function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6301\" class=\"headerLeftMenuInActive\"><a id=\"aID6301\" href=\"#\" OnMouseOver=\"link('_dir','instruction_set0',this)\" class=\"leftMenuLinkHeadInActive\">instruction_set</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID768\" class=\"leftMenuInActive\"><a id=\"aID768\" href=\"#\" OnMouseOver=\"link('_class','InstructionSet58373',this)\" class=\"leftMenuLinkInActive\">InstructionSet</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
