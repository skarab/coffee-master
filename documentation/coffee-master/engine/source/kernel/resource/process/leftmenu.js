function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6321\" class=\"headerLeftMenuInActive\"><a id=\"aID6321\" href=\"#\" OnMouseOver=\"link('_dir','process0',this)\" class=\"leftMenuLinkHeadInActive\">process</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID803\" class=\"leftMenuInActive\"><a id=\"aID803\" href=\"#\" OnMouseOver=\"link('_class','Process24579',this)\" class=\"leftMenuLinkInActive\">Process</a></div>\n");
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
