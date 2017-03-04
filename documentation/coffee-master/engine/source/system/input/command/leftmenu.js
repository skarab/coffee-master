function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6387\" class=\"headerLeftMenuInActive\"><a id=\"aID6387\" href=\"#\" OnMouseOver=\"link('_dir','command0',this)\" class=\"leftMenuLinkHeadInActive\">command</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID897\" class=\"leftMenuInActive\"><a id=\"aID897\" href=\"#\" OnMouseOver=\"link('_class','Command26233',this)\" class=\"leftMenuLinkInActive\">Command</a></div>\n");
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
