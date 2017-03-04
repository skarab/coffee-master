function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6350\" class=\"headerLeftMenuInActive\"><a id=\"aID6350\" href=\"#\" OnMouseOver=\"link('_dir','point0',this)\" class=\"leftMenuLinkHeadInActive\">point</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID852\" class=\"leftMenuInActive\"><a id=\"aID852\" href=\"#\" OnMouseOver=\"link('_class','ComponentLightPoint54809',this)\" class=\"leftMenuLinkInActive\">ComponentLightPoint</a></div>\n");
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
