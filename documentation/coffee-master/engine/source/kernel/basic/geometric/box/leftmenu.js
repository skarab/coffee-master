function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6273\" class=\"headerLeftMenuInActive\"><a id=\"aID6273\" href=\"#\" OnMouseOver=\"link('_dir','box0',this)\" class=\"leftMenuLinkHeadInActive\">box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID733\" class=\"leftMenuInActive\"><a id=\"aID733\" href=\"#\" OnMouseOver=\"link('_class','Box39014',this)\" class=\"leftMenuLinkInActive\">Box</a></div>\n");
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
