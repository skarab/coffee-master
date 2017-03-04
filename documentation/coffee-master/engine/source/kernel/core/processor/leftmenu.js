function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6300\" class=\"headerLeftMenuInActive\"><a id=\"aID6300\" href=\"#\" OnMouseOver=\"link('_dir','processor0',this)\" class=\"leftMenuLinkHeadInActive\">processor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6301\" class=\"leftMenuInActive\"><a id=\"aID6301\" href=\"#\" OnMouseOver=\"link('_dir','instruction_set/instruction_set0',this)\" class=\"leftMenuLinkInActive\">instruction_set</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID767\" class=\"leftMenuInActive\"><a id=\"aID767\" href=\"#\" OnMouseOver=\"link('_class','Processor58373',this)\" class=\"leftMenuLinkInActive\">Processor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6213\" class=\"leftMenuInActive\"><a id=\"aID6213\" href=\"#\" OnMouseOver=\"link('_member','PROCESSOR_TYPE6535345',this)\" class=\"leftMenuLinkInActive\">PROCESSOR_TYPE</a></div>\n");
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
