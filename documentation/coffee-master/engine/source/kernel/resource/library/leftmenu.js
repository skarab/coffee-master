function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6317\" class=\"headerLeftMenuInActive\"><a id=\"aID6317\" href=\"#\" OnMouseOver=\"link('_dir','library0',this)\" class=\"leftMenuLinkHeadInActive\">library</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID800\" class=\"leftMenuInActive\"><a id=\"aID800\" href=\"#\" OnMouseOver=\"link('_class','Library24579',this)\" class=\"leftMenuLinkInActive\">Library</a></div>\n");
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
