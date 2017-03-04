function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6409\" class=\"headerLeftMenuInActive\"><a id=\"aID6409\" href=\"#\" OnMouseOver=\"link('_dir','scene0',this)\" class=\"leftMenuLinkHeadInActive\">scene</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6405\" class=\"leftMenuInActive\"><a id=\"aID6405\" href=\"#\" OnMouseOver=\"link('_dir','bounding/bounding0',this)\" class=\"leftMenuLinkInActive\">bounding</a></div>\n");
document.write("<div id=\"divID6406\" class=\"leftMenuInActive\"><a id=\"aID6406\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6407\" class=\"leftMenuInActive\"><a id=\"aID6407\" href=\"#\" OnMouseOver=\"link('_dir','node/node0',this)\" class=\"leftMenuLinkInActive\">node</a></div>\n");
document.write("<div id=\"divID6408\" class=\"leftMenuInActive\"><a id=\"aID6408\" href=\"#\" OnMouseOver=\"link('_dir','path/path0',this)\" class=\"leftMenuLinkInActive\">path</a></div>\n");
document.write("<div id=\"divID6410\" class=\"leftMenuInActive\"><a id=\"aID6410\" href=\"#\" OnMouseOver=\"link('_dir','transform/transform0',this)\" class=\"leftMenuLinkInActive\">transform</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID930\" class=\"leftMenuInActive\"><a id=\"aID930\" href=\"#\" OnMouseOver=\"link('_class','Resource42087',this)\" class=\"leftMenuLinkInActive\">Resource</a></div>\n");
document.write("<div id=\"divID931\" class=\"leftMenuInActive\"><a id=\"aID931\" href=\"#\" OnMouseOver=\"link('_class','World42087',this)\" class=\"leftMenuLinkInActive\">World</a></div>\n");
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
