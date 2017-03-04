function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6481\" class=\"headerLeftMenuInActive\"><a id=\"aID6481\" href=\"#\" OnMouseOver=\"link('_dir','project0',this)\" class=\"leftMenuLinkHeadInActive\">project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID6168\" class=\"leftMenuInActive\"><a id=\"aID6168\" href=\"#\" OnMouseOver=\"link('_class','Object0',this)\" class=\"leftMenuLinkInActive\">Object</a></div>\n");
document.write("<div id=\"divID1086\" class=\"leftMenuInActive\"><a id=\"aID1086\" href=\"#\" OnMouseOver=\"link('_class','ProjectConfig38803',this)\" class=\"leftMenuLinkInActive\">ProjectConfig</a></div>\n");
document.write("<div id=\"divID1087\" class=\"leftMenuInActive\"><a id=\"aID1087\" href=\"#\" OnMouseOver=\"link('_class','ProjectConfigTarget38803',this)\" class=\"leftMenuLinkInActive\">ProjectConfigTarget</a></div>\n");
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
