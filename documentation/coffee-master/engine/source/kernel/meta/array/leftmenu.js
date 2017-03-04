function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6302\" class=\"headerLeftMenuInActive\"><a id=\"aID6302\" href=\"#\" OnMouseOver=\"link('_dir','array0',this)\" class=\"leftMenuLinkHeadInActive\">array</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID769\" class=\"leftMenuInActive\"><a id=\"aID769\" href=\"#\" OnMouseOver=\"link('_class','Array53261',this)\" class=\"leftMenuLinkInActive\">Array</a></div>\n");
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
