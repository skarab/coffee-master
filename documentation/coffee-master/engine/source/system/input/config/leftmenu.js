function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6388\" class=\"headerLeftMenuInActive\"><a id=\"aID6388\" href=\"#\" OnMouseOver=\"link('_dir','config0',this)\" class=\"leftMenuLinkHeadInActive\">config</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID898\" class=\"leftMenuInActive\"><a id=\"aID898\" href=\"#\" OnMouseOver=\"link('_class','Config26233',this)\" class=\"leftMenuLinkInActive\">Config</a></div>\n");
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
